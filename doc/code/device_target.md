# 장비 작동 대상

장비가 작동하는 대상을 구분하는 것은 중요하다. 예를 들어 온도센서의 경우 대상을 땅으로 하면 지온이 되고, 대기로 하면 기온이 되고, 작물로 하면 작물 온도가 된다. 따라서 해당 센서가 작동하는 대상을 지정할 수 있어야 한다.

장비가 작동하는 대상번호는 다음과 같다.

| 이름 | 그룹 | 번호 | 대상 | 설명 |
|:--------:|:--------:|:--------:|:--------:|:--------|
| DO_UNKNOWN | 없음 | 1 | 없음 | 장비의 대상이 없는 경우 혹은 특정하기 어려운 경우  |
| DO_ENV_ATMOSPHERE | 환경 | 1001 | 대기 | 대기를 대상으로 하는 경우 ex. 온도, 습도 |
| DO_ENV_SOIL | 환경 | 1002 | 토양 | 토양을 대상으로 하는 경우 ex. 지온, 지습, EC |
| DO_ENV_NUTRIENTSOLUTION | 환경 | 1003 | 양액 | 양액을 대상으로 하는 경우 ex. EC, pH |
| DO_PLANT_STEM | 작물 | 2001 | 줄기 | 작물의 줄기를 대상으로 하는 경우 |
| DO_PLANT_LEAF | 작물 | 2002 | 잎 | 작물의 잎을 대상으로하는 경우 |
| DO_PLANT_FRUIT | 작물 | 2003 | 과실 | 작물의 과실을 대상으로 하는 경우 |
| DO_PLANT_ROOT | 작물 | 2004 | 뿌리 | 작물의 뿌리를 대상으로 하는 경우 |
| DO_EQUIPMENT | 설비 | 3001 | 설비 | 설비를 대상으로 하는 경우 ex. 창(방향구분이 없는 창), 팬 |
| DO_EQUIPMENT_NORTH | 설비 | 3002 | 북측설비 | 북쪽을 기준으로 시계방향으로 봤을때 가까운 설비를 대상으로 하는 경우 ex. 우측창 |
| DO_EQUIPMENT_SOUTH | 설비 | 3003 | 남측설비 | 북쪽을 기준으로 시계방향으로 봤을때 먼 설비를 대상으로 하는 경우 ex. 좌측창 |

**(구동기에 대한 특이사항을 정리할 방안이 필요할 수 있다. 예를 들어 3중창같은 경우!!)**

```
typedef enum {
    DO_UNKNOWN = 1,
    DO_ENV_ATMOSPHERE = 1001,
    DO_ENV_SOIL = 1002,
    DO_ENV_NUTRIENTSOLUTION = 1003,
    DO_PLANT_STEM = 2001,
    DO_PLANT_LEAF = 2002,
    DO_PLANT_FRUIT = 2003,
    DO_PLANT_ROOT = 2004,
    DO_EQUIPMENT = 3001,
    DO_EQUIPMENT_NORTH = 3002,
    DO_EQUIPMENT_SOUTH = 3003
} devtarget_t;
```
