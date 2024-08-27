#pragma once;


namespace multiplayer 
{
    // The union allows you to convert the keypress data
    // to a single 'int' to be able to send it over link.
    union keypad_data {
        struct keypad_data_struct {
            int start_pressed : 1;
            
            int l_pressed : 1;
            int r_pressed : 1;
            int up_pressed : 1;
            int down_pressed : 1;
            int left_pressed: 1;
            int right_pressed: 1;
            int a_pressed : 1;
            int b_pressed : 1;

            int left_held : 1;
            int right_held : 1;

            int select_pressed : 1;
        } keypad_data;
        
        int data;
    };


    enum signal: int {
        signal_start_game = 65533,

        signal_sync_x = 65532,
        signal_sync_y = 65531,
        signal_sync_health = 65530
    };




    // Multiplayer
    int players_counter = 1;
    int current_player_id = 0; 

    keypad_data last_keypad_data_to_send;
    keypad_data other_player_keypad_data;



    keypad_data read_keys() {
        return keypad_data  {
            keypad_data: multiplayer::keypad_data::keypad_data_struct {
                start_pressed: bn::keypad::start_pressed(),
                l_pressed: bn::keypad::l_pressed(),
                r_pressed: bn::keypad::r_pressed(),
                up_pressed: bn::keypad::up_pressed(),
                down_pressed: bn::keypad::down_pressed(),
                left_pressed: bn::keypad::left_pressed(),
                right_pressed: bn::keypad::right_pressed(),
                a_pressed: bn::keypad::a_pressed(),
                left_held: bn::keypad::left_held(),
                right_held: bn::keypad::right_held(),
                select_pressed: bn::keypad::select_pressed()
            }
        };
    }

    void send_if_changed(keypad_data kpdt) {
        if (multiplayer::last_keypad_data_to_send.data != kpdt.data) {
            bn::link::send(kpdt.data);   
            multiplayer::last_keypad_data_to_send.data = kpdt.data;
        }
    }

    void receive_keypad_data() {
        if(bn::optional<bn::link_state> link_state = bn::link::receive()) {
            const bn::link_player& first_other_player = link_state->other_players().front();
            multiplayer::other_player_keypad_data.data = first_other_player.data();

            BN_LOG(bn::format<40>("received: {}", multiplayer::other_player_keypad_data.data));                

            // Update multiplayer info text
            if (multiplayer::players_counter != link_state->player_count()) {
                multiplayer::players_counter = link_state->player_count();
                multiplayer::current_player_id = link_state->current_player_id();

                // Immediately refresh the other player as well
                // bn::link::send(keypad_data_to_send.data);   
                BN_LOG("change in link");                
                // bn::string<40> info_text = bn::format<40>("players: {}, player id: {}", multiplayer::players_counter, multiplayer::current_player_id);
                // printer->print(info_text);
            }
        }
    }
}
