# 장비 종류

장비종류는 devtype_t 로 표현된다.

| 이름 | 분류번호 | 번호 | 분류 | 장비 | 설명 |
|:--------|--------:|:--------:|:--------:|--------:|:--------|
| DT_DEV_UNKNOWN | 0 | 0 | 기타장비 | 알수없는 장비 | 코드에 없는 장비인 경우. |
| DT_SEN_TEMPERATURE | 1 | 10001 | 센서 | 온도센서 | 온도를 측정하는 센서. |
| DT_SEN_HUMIDITY | 1 | 10002 | 센서 | 습도센서 | 습도를 측정하는 센서. |
| DT_SEN_UNKNOWN | 1 | 19000 | 센서 | 알수없는 센서 | 코드에 없는 센서인 경우. |
| DT_MOT_WINDOW | 2 | 20001 | 모터형 구동기 | 창 구동기 | 창을 구동하는 모터형 구동기. |
| DT_MOT_UNKNOWN | 2 | 29000 | 모터형 구동기 | 알수없는 모터형 구동기 | 코드에 없는 모터형 구동기인 경우. |
| DT_SWC_FAN | 3 | 30001 | 스위치형 구동기 | 팬 | 팬 |
| DT_SWC_UNKNOWN | 3 | 39000 | 스위치형 구동기 | 알수없는 스위치형 구동기 | 코드에 없는 스위치형 구동기인 경우. |

알수없는 센서, 구동기, 장비의 경우 9000 번 이후의 번호는 개별 구현에서 충돌하지 않도록 사용할 수 있다. 이 경우 개발사 번호와 매칭시켜서 판단한다.

```
typedef enum {
  DG_UNKNOWN = 0
  DG_SENSOR = 1,
  DG_MOTOR = 2,
  DG_SWITCH = 3,
} devgroup_t;

typedef enum {
  DT_SEN_TEMPERATURE = 10001,
  DT_SEN_HUMIDITY = 10002,
  DT_SEN_UNKNOWN = 19000,
  DT_MOT_WINDOW = 20001,
  DT_MOT_UNKNOWN = 29001,
  DT_SWC_FAN = 30001,
  DT_SWC_UNKNOWN = 39001,
  DT_DEV_UNKNOWN = 49001,
} devtype_t;
```
