#pragma once;


namespace multiplayer 
{
    // The union allows you to convert the keypress data
    // to a single 'int' to be able to send it over link.
    union keypad_data {
        struct keypad_data_struct {
            int l_pressed : 1;
            int r_pressed : 1;
            int a_pressed : 1;
            int b_pressed : 1;

            int left_held : 1;
            int right_held : 1;
        } keypad_data;
        
        int data;
    };


    enum signal: int {
        signal_start_game = 65533,

        signal_sync_x = 65532,
        signal_sync_y = 65531,
        signal_sync_health = 65530
    };
}
