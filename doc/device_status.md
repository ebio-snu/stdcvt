# 장비 상태

장비상태는 devstat_t 로 표현된다.

| 이름 | 번호 | 대상장비 | 설명 |
|:--------|--------:|:--------:|:--------|
| DS_DEV_ABNORMAL | 1 | 모든장비 | 장비가 정상적으로 동작하지 않음. 연결이 끊어지는 경우 포함. |
| DS_SEN_NORMAL | 101 | 센서 | 센서가 정상적으로 동작함. |
| DS_SWC_ON | 201 | 스위치 | 스위치가 작동중임. |
| DS_SWC_OFF | 202 | 스위치 | 스위치가 중지상태임. |
| DS_MOT_OPEN | 301 | 모터 | 모터가 열리는 방향으로 작동중임. |
| DS_MOT_CLOSE | 302 | 모터 | 모터가 닫히는 방향으로 작동중임. |
| DS_MOT_STOP | 303 | 모터 | 모터가 중지상태임. |

```
typedef enum {
  DS_DEV_ABNORMAL = 1,
  DS_SEN_NORMAL = 101,
  DS_SWC_ON = 201,
  DS_SWC_OFF = 202,
  DS_MOT_OPEN = 301,
  DS_MOT_CLOSE = 302,
  DS_MOT_STOP = 303
} devstat_t;
```
