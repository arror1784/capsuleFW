#ifndef COMMON_H
#define COMMON_H

//#define MCU_UPDATE_TEST
#define TEST_WITHOUT_SERIAL

#define PRINT_MOVE_NULL             -1
#define PRINT_MOVE_WAIT             0
#define PRINT_MOVE_UP               1
#define PRINT_MOVE_DOWN             2
#define PRINT_MOVE_INIT             3
#define PRINT_MOVE_FINISH           4
#define PRINT_MOVE_READY            5
#define PRINT_MOVE_AUTOHOME         6
#define PRINT_MOVE_LAYER            7
#define PRINT_MOVE_BEDCURRENT       10
#define PRINT_CANCLE                11

#define PRINT_START                 11
#define PRINT_PAUSE                 12
#define PRINT_RESUME                13

#define IMAGE_CHANGE                20

#define PRINT_DLP_WORKING           8
#define PRINT_DLP_NOT_WORKING       9
#define PRINT_DLP_WORK_FINISH       10

#define PRINT_MOVE_UP_OK            101
#define PRINT_MOVE_DOWN_OK          102
#define PRINT_MOVE_INIT_OK          103
#define PRINT_MOVE_FINISH_OK        104
#define PRINT_MOVE_AUTOHOME_OK      105
#define PRINT_MOVE_LAYER_OK         106
#define PRINT_MOVE_READY_OK         107

#define BED_WORK                    1
#define BED_NOT_WORK                2
#define BED_PAUSE                   3
#define BED_FINISH_WORK             6
#define BED_PAUSE_WORK              7
#define BED_ERROR_WORK              9

#define DLP_STATUS_ON               0x01
#define DLP_STATUS_OFF              0x02

#define SHORT_BUTTON                100
#define LONG_BUTTON                 101
#define MOVE_OK                     110
#define SHUTDOWN                    120

#define LCD_OFF                     131
#define LCD_ON                      132

#define BED_IMAGE_LOADED            1
#define BED_IMAGE_NONE              2

#define DLP_POWER_ON                true
#define DLP_POWER_OFF               false

#define SET_LED_GREEN               50
#define SET_LED_BLUE                51
#define SET_LED_RED                 52

#define TARGET_BOARD_VID            403
#define TARGET_BOARD_PID            6001



#endif // COMMON_H
