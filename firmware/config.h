#ifndef CONFIG_H
#define CONFIG_H

#define BTN_DEBOUNCE      20   // дребезг кнопок (мсек.)
#define BTN_DCGAP         100  // время между двойным кликом (мсек.)
#define BTN_HOLDTIME      1000 // время зажатия кнопки (мсек.)
#define BTN_LONGHOLDTIME  3000 // время долгого нажатия кнопки  (мсек.)

#define SET_STEP          5    // шаг настрек

#define MOT_MAX_SPEED     900  // моторы
#define MOT_ACC_PUSH      50   // (1-100)
#define MOT_SPEED_PUSH    30   // (1-100)
#define MOT_STEP_PUSH     20   // (1-100)
#define MOT_SPEED_PULL    50   // (1-100)
#define MOT_STEP_PULL     5    // (1-100)

#endif
