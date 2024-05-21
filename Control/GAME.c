#include "GAME.h"

Game_TypeDef game;

void game_init(Game_TypeDef *Game){
    Game->Round=GAME_ROUND0;
    Game->State=0;
    Game->Direction=GAME_RIGHT;
}

void game_play(Game_TypeDef *Game){
    uint8_t i=0;
    if(Game->Round==GAME_ROUND1){
        printf("Game 1 start\r\n");
        OLED_ShowString(1,3,"1 ok");
        for(i=0;i<7;i++) Delay_ms(1000);
        /* first ball */
        servo_down(&servo);
        Motor_Straight(30);

        /*straight time 14363ms*/
        for(i=0;i<14;i++) Delay_ms(1000);
        Delay_ms(363);

        Motor_Stop(&motor);
        Delay_ms(100);

        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30);

        /*horizontal time 9869ms*/
        for(i=0;i<9;i++) Delay_ms(1000);
        Delay_ms(869);

        Motor_Stop(&motor);
        Delay_ms(100);

        if(Game->Direction==GAME_RIGHT) Motor_Rote(30);
        else Motor_Rote(-30);
        Delay_ms(1);
        if(Game->Direction==GAME_RIGHT) Motor_Rote(30);
        else Motor_Rote(-30);

        Delay_ms(1000);
        Delay_ms(1000);
        Delay_ms(20);
        //for(i=0;i<GAME1_ANGLE_TIME;i++) Delay_ms(1);
        //Delay_ms(GAME1_ANGLE_TIME);
        Motor_Stop(&motor);

        Delay_ms(1000);
        valve_hit(VALVE_TIME);
        Delay_ms(VALVE_TIME);
        if(Game->Direction==GAME_RIGHT) Motor_Rote(-30);
        else Motor_Rote(30);
        Delay_ms(1000);
        Delay_ms(1000);
        Delay_ms(20);
        Motor_Stop(&motor);
        Delay_ms(100);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);

        /*horizontal time 9869ms*/
        for(i=0;i<9;i++) Delay_ms(1000);
        Delay_ms(869);

        Motor_Stop(&motor);
        Delay_ms(100);
        Motor_Straight(-30);

        /*straight time 14363ms*/
        for(i=0;i<14;i++) Delay_ms(1000);
        Delay_ms(363);

        Motor_Stop(&motor);
        Delay_ms(100);
        #if 0
        servo_view_ball(&servo);
        Delay_ms(100);
        /* second ball */
        if(Game->Direction==GAME_RIGHT) Motor_Rote(-30);
        else Motor_Rote(30);
        Delay_ms(1000);
        Delay_ms(1000);
        Delay_ms(199);
        Motor_Stop(&motor);
        Delay_ms(100);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);
        /* search ball */
        while(tof.Distance>2000) TOF_GetData(&tof);
        Motor_Stop(&motor);
        openmv_set(&cv,OPENMV_BASKETBALL);
        //Delay_ms(GAME_WAIT_DETECT_TIME);
        Delay_ms(1000);
        Delay_ms(500);
        if(cv.Flag==FALSE){
            /* try to find ball again */
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
            else Motor_Horizontal(30);
            Delay_ms(GAME_LEAVE_BALL_TIME);
            Motor_Stop(&motor);
            Delay_ms(100);
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
            else Motor_Horizontal(30);    
            while(tof.Distance>2000) TOF_GetData(&tof);
            Motor_Stop(&motor);
            openmv_set(&cv,OPENMV_BASKETBALL);
            Delay_ms(1000);
            Delay_ms(500);
            if(cv.Flag==FALSE){
                /* try to find ball again */
                if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
                else Motor_Horizontal(30);
                Delay_ms(GAME_LEAVE_BALL_TIME);
                Motor_Stop(&motor);
                Delay_ms(100);
                if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
                else Motor_Horizontal(30);    
                while(tof.Distance>2000) TOF_GetData(&tof);
                Motor_Stop(&motor);
                Delay_ms(GAME_LEAVE_BALL_TIME);
            }
        }
        /* aim ball */
        Expert_Set(&expert,OPENMV_SCREEN_MID,MODE_HORIZONTAL);
        Expert_Enable(&expert);
        Expert_Control(&expert);
        Delay_ms(1);
        while (expert.Enable==ENABLE){}
        /* near ball */
        servo_down(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        Motor_Straight(30);
        while(tof.Distance>TOF_LIFT_DISTANCE) TOF_GetData(&tof);
        Motor_Stop(&motor);
        servo_up(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        servo_down(&servo);
        /* hit ball */
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30);  
        Delay_ms(1000);
        Delay_ms(899);
        Motor_Stop(&motor);
        Delay_ms(1000);
        valve_hit(VALVE_TIME);
        Delay_ms(1000);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);  
        Delay_ms(1000);
        Delay_ms(899);
        Motor_Stop(&motor);
        #endif
    }
    else if(Game->Round==GAME_ROUND2){
        printf("Game 2 start\r\n");
        OLED_ShowString(1,3,"2 ok");
        for(i=0;i<7;i++) Delay_ms(1000);
        servo_down(&servo);
        Motor_Straight(30);

        /*straight time 14363ms*/
        for(i=0;i<14;i++) Delay_ms(1000);
        Delay_ms(363);

        Motor_Stop(&motor);
        Delay_ms(100);
        
        /*search init*/
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30);
        for(i=0;i<3;i++) Delay_ms(1000);
        Motor_Stop(&motor);
        Delay_ms(100);

        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);
        for(i=0;i<3;i++) Delay_ms(1000);
        Motor_Stop(&motor);
        Delay_ms(100);

        Motor_Straight(-30);

        /*straight time 14363ms*/
        for(i=0;i<14;i++) Delay_ms(1000);
        Delay_ms(363);

        Motor_Stop(&motor);
        Delay_ms(100);
        #if 0
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30);
        while(tof.Distance<2000) TOF_GetData(&tof);
        Motor_Stop(&motor);
        servo_view_ball(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        openmv_set(&cv,OPENMV_BASKETBALL);
        Delay_ms(1000);
        Delay_ms(500);
        //Delay_ms(GAME_WAIT_DETECT_TIME);
        if(cv.Flag==FALSE){
            /* try to find ball again */
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
            else Motor_Horizontal(-30);
            Delay_ms(GAME_LEAVE_BALL_TIME);
            Motor_Stop(&motor);
            Delay_ms(100);
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
            else Motor_Horizontal(-30);
            while(tof.Distance<8000) TOF_GetData(&tof);
            Motor_Stop(&motor);
            openmv_set(&cv,OPENMV_BASKETBALL);
            Delay_ms(1000);
            Delay_ms(500);
            //Delay_ms(GAME_WAIT_DETECT_TIME);
            if(cv.Flag==FALSE){
                /* try to find ball again */
                if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
                else Motor_Horizontal(-30);
                Delay_ms(GAME_LEAVE_BALL_TIME);
                Motor_Stop(&motor);
                Delay_ms(100);
                if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
                else Motor_Horizontal(-30);
                while(tof.Distance<2000) TOF_GetData(&tof);
                Motor_Stop(&motor);
                Delay_ms(1000);
            }
        }
        /* aim ball */
        Expert_Set(&expert,OPENMV_SCREEN_MID,MODE_HORIZONTAL);
        Expert_Enable(&expert);
        Expert_Control(&expert);
        Delay_ms(1);
        while (expert.Enable==ENABLE){}
        /* near ball */
        servo_down(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        Motor_Straight(30);
        while(tof.Distance>TOF_LIFT_DISTANCE) TOF_GetData(&tof);
        Motor_Stop(&motor);
        servo_up(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        servo_down(&servo);
        /* hit ball */
        if(Game->Direction==GAME_RIGHT) Motor_Rote(30);
        else Motor_Rote(-30);  
        //Delay_ms(GAME1_ANGLE_TIME);
        Delay_ms(1000);
        Delay_ms(1000);
        Delay_ms(199);
        Motor_Stop(&motor);
        valve_hit(VALVE_TIME);
        Delay_ms(1000);
        if(Game->Direction==GAME_RIGHT) Motor_Rote(-30);
        else Motor_Rote(30);  
        //Delay_ms(GAME1_ANGLE_TIME);
        Delay_ms(1000);
        Delay_ms(1000);
        Delay_ms(199);
        Motor_Stop(&motor);
        Delay_ms(100);
        #endif
    }
    else if(Game->Round==GAME_ROUND3){
        printf("Game 3 start\r\n");
        OLED_ShowString(1,3,"3 ok");
        for(i=0;i<7;i++) Delay_ms(1000);
        servo_down(&servo);
        Motor_Straight(30);

        /*straight time 14363ms*/
        for(i=0;i<14;i++) Delay_ms(1000);
        Delay_ms(363);

        Motor_Stop(&motor);
        Delay_ms(100);
        
        /*search init*/
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30);

        //for(i=0;i<3;i++) Delay_ms(1000);
        while(tof.Distance>2000) TOF_GetData(&tof);
        Motor_Stop(&motor);
        Delay_ms(100);
        Motor_Straight(30);
        while(tof.Distance>TOF_LIFT_DISTANCE) TOF_GetData(&tof);
        Motor_Stop(&motor);
        Delay_ms(100);

        servo_up(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        servo_down(&servo);
        if(Game->Direction==GAME_RIGHT) Motor_Rote(30);
        else Motor_Rote(-30);
        Delay_ms(1000);
        Delay_ms(800);
        Motor_Stop(&motor);
        Delay_ms(100);
        valve_hit(VALVE_TIME);
        Delay_ms(1000);
        if(Game->Direction==GAME_RIGHT) Motor_Rote(-30);
        else Motor_Rote(30);
        Delay_ms(1000);
        Delay_ms(800);
        Motor_Stop(&motor);
        Motor_Straight(-30);

        /*straight time 14363ms*/
        for(i=0;i<14;i++) Delay_ms(1000);
        Delay_ms(363);

        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);
        for(i=0;i<3;i++) Delay_ms(1000);
        Motor_Stop(&motor);
        Delay_ms(100);

        Motor_Straight(-30);
        #if 0
        for(i=0;i<7;i++) Delay_ms(1000);
        servo_down(&servo);
        /* first ball */
        Motor_Straight(-30);
        for(i=0;i<9;i++) Delay_ms(1000);
        Delay_ms(618);
        Motor_Stop(&motor);
        Delay_ms(100);
        /*find mark bucket*/
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30); 
        while(tof.Distance>1600) TOF_GetData(&tof);
        Motor_Stop(&motor);
        Delay_ms(100);
        if(Game->Direction==GAME_RIGHT) Motor_Rote(-30);
        else Motor_Rote(30);
        //Delay_ms(GAME_ANGLE90_TIME);
        Delay_ms(1000);
        Delay_ms(800);
        Motor_Stop(&motor);
        Delay_ms(100);
        servo_view_ball(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);  
        while(tof.Distance>2000) TOF_GetData(&tof);
        Motor_Stop(&motor);
        
        openmv_set(&cv,OPENMV_BASKETBALL);
        //Delay_ms(GAME_WAIT_DETECT_TIME);
        Delay_ms(1000);
        Delay_ms(500);
        if(cv.Flag==FALSE){
            /* try to find ball again */
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
            else Motor_Horizontal(30);
            Delay_ms(GAME_LEAVE_BALL_TIME);
            Motor_Stop(&motor);
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
            else Motor_Horizontal(-30);
            while(tof.Distance<2000) TOF_GetData(&tof);
            Motor_Stop(&motor);
            openmv_set(&cv,OPENMV_BASKETBALL);
            Delay_ms(1000);
            Delay_ms(500);
            if(cv.Flag==FALSE){
                if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
                    else Motor_Horizontal(30);
                    Delay_ms(GAME_LEAVE_BALL_TIME);
                    Motor_Stop(&motor);
                    if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
                    else Motor_Horizontal(-30);
                    while(tof.Distance<2000) TOF_GetData(&tof);
                    Motor_Stop(&motor);
                    Delay_ms(1000);
                    Delay_ms(500);
            }
        }
        /* aim ball */
        Expert_Set(&expert,OPENMV_SCREEN_MID,MODE_HORIZONTAL);
        Expert_Enable(&expert);
        Expert_Control(&expert);
        Delay_ms(1);
        while (expert.Enable==ENABLE){}
        Delay_ms(100);
        /* near ball */
        servo_down(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        Motor_Straight(30);
        while(tof.Distance>TOF_LIFT_DISTANCE) TOF_GetData(&tof);
        Motor_Stop(&motor);
        Delay_ms(100);
        servo_up(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        servo_down(&servo);
        /* hit ball */
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);  
        while(tof.Distance<8000) return;
        Motor_Stop(&motor);
        Delay_ms(100);
        //Delay_ms(GAME1_ANGLE_TIME);
        //Motor_Stop(&motor);
        valve_hit(VALVE_TIME);
        Delay_ms(1000);
        //if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        //else Motor_Horizontal(30);  
        //Delay_ms(GAME1_ANGLE_TIME);
        //Motor_Stop(&motor);
        #endif
    }
    else if(Game->Round==GAME_ROUND4){
        printf("Game 4 start\r\n");
        OLED_ShowString(1,3,"4 ok");
        for(i=0;i<7;i++) Delay_ms(1000);
        //servo_down(&servo);
        servo.Angle=590;
        servo.Time=2000;
        servo.ID=1;
        servo_control(&servo);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);
        for(i=0;i<12;i++) Delay_ms(1000);
        Delay_ms(406);
        Motor_Stop(&motor);
        Delay_ms(100);
        Motor_Straight(30);
        for(i=0;i<23;i++) Delay_ms(1000);
        Delay_ms(18);
        Motor_Stop(&motor);
        Delay_ms(100);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);
        for(i=0;i<6;i++) Delay_ms(1000);
        Delay_ms(893);
        Motor_Stop(&motor);
        Delay_ms(100);
        valve_hit(VALVE_TIME);
        Delay_ms(VALVE_TIME);
        Motor_Straight(-30);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30);
        for(i=0;i<6;i++) Delay_ms(1000);
        Delay_ms(893);
        Motor_Stop(&motor);
        Delay_ms(100);
        Motor_Straight(-30);
        for(i=0;i<23;i++) Delay_ms(1000);
        Delay_ms(18);
        Motor_Stop(&motor);
        Delay_ms(100);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30);
        for(i=0;i<12;i++) Delay_ms(1000);
        Delay_ms(406);
        Motor_Stop(&motor);
        Delay_ms(100);
        #if 0
        Motor_Straight(-30);
        for(i=0;i<9;i++) Delay_ms(1000);
        Delay_ms(618);
        Motor_Stop(&motor);
        Delay_ms(100);
        /* find mark bucket*/
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);
        while(tof.Distance>1600) TOF_GetData(&tof);
        Motor_Stop(&motor);
        Delay_ms(100);
        /*move to middle*/
        Motor_Straight(-30);
        //while(tof.Distance<3500) TOF_GetData(&tof);
        //Motor_Stop(&motor);
        for(i=0;i<7;i++) Delay_ms(1000);
        Delay_ms(80);
        /* aim target */
        if(Game->Direction==GAME_RIGHT) Motor_Rote(-30);
        else Motor_Rote(30);
        Delay_ms(GAME_ANGLE90_TIME);
        Motor_Stop(&motor);
        Delay_ms(500);
        /*hit ball*/
        valve_hit(VALVE_TIME);
        Delay_ms(VALVE_TIME);
        /*find the second ball*/
        if(Game->Direction==GAME_RIGHT) Motor_Rote(-30);
        else Motor_Rote(30);
        Delay_ms(GAME_ANGLE90_TIME);
        Motor_Stop(&motor);
        Motor_Straight(-30);
        Delay_ms(4000);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);
        while (tof.Distance>1500) TOF_GetData(&tof);
        Motor_Stop(&motor);
        Delay_ms(100);
        servo_view_ball(&servo);
        Delay_ms(2000);
        openmv_set(&cv,OPENMV_VOLLEYBALL);
        Delay_ms(GAME_WAIT_DETECT_TIME);
        if(cv.Flag==FALSE){
            /* try to find ball again */
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
            else Motor_Horizontal(30);
            Delay_ms(GAME_LEAVE_BALL_TIME);
            Motor_Stop(&motor);
            Delay_ms(100);
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
            else Motor_Horizontal(-30);
            while(tof.Distance<2000) TOF_GetData(&tof);
            Motor_Stop(&motor);
            openmv_set(&cv,OPENMV_VOLLEYBALL);
            Delay_ms(GAME_WAIT_DETECT_TIME);
            if(cv.Flag==FALSE){
                if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
                    else Motor_Horizontal(30);
                    Delay_ms(GAME_LEAVE_BALL_TIME);
                    Motor_Stop(&motor);
                    Delay_ms(100);
                    if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
                    else Motor_Horizontal(-30);
                    while(tof.Distance<2000) TOF_GetData(&tof);
                    Motor_Stop(&motor);
                    Delay_ms(GAME_WAIT_DETECT_TIME);
            }
        }
        /* aim ball */
        Expert_Set(&expert,OPENMV_SCREEN_MID,MODE_HORIZONTAL);
        Expert_Enable(&expert);
        Expert_Control(&expert);
        Delay_ms(1);
        while (expert.Enable==ENABLE){}
        /* near ball */
        servo_down(&servo);
        Delay_ms(2000);
        Motor_Straight(30);
        while(tof.Distance>TOF_LIFT_DISTANCE) TOF_GetData(&tof);
        Motor_Stop(&motor);
        servo_up(&servo);
        Delay_ms(2000);
        servo_down(&servo);
        /*find mark bucket*/
        //if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        //else Motor_Horizontal(-30);
        //Delay_ms(GAME_ANGLE90_TIME);
        //Motor_Stop(&motor);
        //Delay_ms(100);
        //while(tof.Distance>4000) TOF_GetData(&tof);
        //Motor_Stop(&motor);
        //Delay_ms(500);
        /*hit ball*/
        if(Game->Direction==GAME_RIGHT) Motor_Rote(30);
        else Motor_Rote(-30);
        Delay_ms(GAME_ANGLE90_TIME);
        Motor_Stop(&motor);
        Delay_ms(500);
        valve_hit(VALVE_TIME);
        Delay_ms(VALVE_TIME);
        /*back*/
        Motor_Horizontal(-30);
        while(tof.Distance<10000) TOF_GetData(&tof);
        Motor_Stop(&motor);
        /*home*/
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30);
        for(i=0;i<2;i++){
            Delay_ms(1000);
        }
        Motor_Stop(&motor);
        #endif
    }
    else if(Game->Round==GAME_ROUND5){
        printf("Game 5 start\r\n");
        OLED_ShowString(1,3,"5 ok");
        for(i=0;i<7;i++) Delay_ms(1000);
        servo_down(&servo);
        Motor_Straight(30);
        /*straight time 14363ms*/
        for(i=0;i<14;i++) Delay_ms(1000);
        Delay_ms(363);
        Motor_Stop(&motor);
        Delay_ms(100);
        Motor_Rote(30);
        Delay_ms(1000);
        Motor_Rote(-30);
        Delay_ms(1000);
        #if 0
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);
        Delay_ms(1000);
        Motor_Stop(&motor);
        Delay_ms(100);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30);
        while(tof.Distance<2000) TOF_GetData(&tof);
        Motor_Stop(&motor);
        Delay_ms(100);
        servo_view_ball(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        openmv_set(&cv,OPENMV_VOLLEYBALL);
        Delay_ms(GAME_WAIT_DETECT_TIME);
        if(cv.Flag==FALSE){
            /* try to find ball again */
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
            else Motor_Horizontal(-30);
            Delay_ms(GAME_LEAVE_BALL_TIME);
            Motor_Stop(&motor);
            Delay_ms(100);
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
            else Motor_Horizontal(-30);
            while(tof.Distance<2000) TOF_GetData(&tof);
            Motor_Stop(&motor);
            Delay_ms(1000);
            Delay_ms(500);
            //Delay_ms(GAME_WAIT_DETECT_TIME);
            if(cv.Flag==FALSE){
                /* try to find ball again */
                if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
                else Motor_Horizontal(-30);
                Delay_ms(GAME_LEAVE_BALL_TIME);
                Motor_Stop(&motor);
                Delay_ms(100);
                if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
                else Motor_Horizontal(-30);
                while(tof.Distance<2000) TOF_GetData(&tof);
                Motor_Stop(&motor);
                Delay_ms(1000);
            }
        }
        /* aim ball */
        Expert_Set(&expert,OPENMV_SCREEN_MID,MODE_HORIZONTAL);
        Expert_Enable(&expert);
        Expert_Control(&expert);
        Delay_ms(1);
        while (expert.Enable==ENABLE){}
        Delay_ms(100);
        /* near ball */
        servo_down(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        Motor_Straight(30);
        while(tof.Distance>TOF_LIFT_DISTANCE) TOF_GetData(&tof);
        Motor_Stop(&motor);
        servo_up(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        servo_down(&servo);
        /* hit ball */
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30);  
        //Delay_ms(GAME_ANGLE90_TIME);
        Delay_ms(1000);
        Delay_ms(800);
        Motor_Stop(&motor);
        valve_hit(VALVE_TIME);
        Delay_ms(1000);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);  
        //Delay_ms(GAME_ANGLE90_TIME);
        Delay_ms(1000);
        Delay_ms(800);
        Motor_Stop(&motor);
        #endif
    }
    else if(Game->Round==GAME_ROUND6){
        printf("Game 6 start\r\n");
        OLED_ShowString(1,3,"6 ok");
        for(i=0;i<7;i++) Delay_ms(1000);
        servo_down(&servo);
        /* first ball */
        Motor_Straight(30);
        /*straight time 14363ms*/
        for(i=0;i<14;i++) Delay_ms(1000);
        Delay_ms(363);
        Motor_Stop(&motor);
        Delay_ms(100);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30); 
        for(i=0;i<2;i++){
            Delay_ms(1000);
        }
        Motor_Stop(&motor);
        Delay_ms(500);
        Motor_Straight(30);
        for(i=0;i<10;i++){
            Delay_ms(1000);
        }
        Motor_Stop(&motor);
        Delay_ms(500);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);  
        while(tof.Distance>2000) TOF_GetData(&tof);
        Motor_Stop(&motor);
        servo_view_ball(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        openmv_set(&cv,OPENMV_VOLLEYBALL);
        Delay_ms(1000);
        Delay_ms(500);
        //Delay_ms(GAME_WAIT_DETECT_TIME);
        if(cv.Flag==FALSE){
            /* try to find ball again */
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
            else Motor_Horizontal(30);
            Delay_ms(GAME_LEAVE_BALL_TIME);
            Motor_Stop(&motor);
            if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
            else Motor_Horizontal(-30);
            while(tof.Distance<2000) TOF_GetData(&tof);
            Motor_Stop(&motor);
            openmv_set(&cv,OPENMV_VOLLEYBALL);
            Delay_ms(1000);
            Delay_ms(500);
            //Delay_ms(GAME_WAIT_DETECT_TIME);
            if(cv.Flag==FALSE){
                if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
                    else Motor_Horizontal(30);
                    Delay_ms(GAME_LEAVE_BALL_TIME);
                    Motor_Stop(&motor);
                    if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
                    else Motor_Horizontal(-30);
                    while(tof.Distance<2000) TOF_GetData(&tof);
                    Motor_Stop(&motor);
                    Delay_ms(1000);
                    Delay_ms(500);
            }
        }
        /* aim ball */
        Expert_Set(&expert,OPENMV_SCREEN_MID,MODE_HORIZONTAL);
        Expert_Enable(&expert);
        Expert_Control(&expert);
        Delay_ms(1);
        while (expert.Enable==ENABLE){}
        /* near ball */
        servo_down(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        Motor_Straight(30);
        while(tof.Distance>TOF_LIFT_DISTANCE) TOF_GetData(&tof);
        Motor_Stop(&motor);
        servo_up(&servo);
        Delay_ms(1000);
        Delay_ms(1000);
        servo_down(&servo);
        /* hit ball */
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(30);
        else Motor_Horizontal(-30);  
        Delay_ms(1000);
        Delay_ms(800);
        Motor_Stop(&motor);
        valve_hit(VALVE_TIME);
        Delay_ms(1000);
        if(Game->Direction==GAME_RIGHT) Motor_Horizontal(-30);
        else Motor_Horizontal(30);  
        Delay_ms(1000);
        Delay_ms(800);
        Motor_Stop(&motor);
    }
    else if(Game->Round==7){
        servo_view_ball(&servo);
        Delay_ms(2000);
        Motor_Horizontal(30);
        while(tof.Distance>2000) TOF_GetData(&tof);
        Motor_Stop(&motor);
        Delay_ms(100);
        openmv_set(&cv,0);
        Delay_ms(GAME_WAIT_DETECT_TIME);
        Expert_Set(&expert,OPENMV_SCREEN_MID,MODE_HORIZONTAL);
        Expert_Enable(&expert);
        Expert_Control(&expert);
        Delay_ms(1);
        while (expert.Enable==ENABLE){}
        Motor_Stop(&motor);
        Delay_ms(100);
        servo_down(&servo);
        Delay_ms(2000);
    }
    /*
    if(Game->Round>GAME_ROUND0){
        Motor_Stop(&motor);
        Game->Round=GAME_ROUND0;
        Game->Direction=GAME_RIGHT;
    }
    */
    
}


