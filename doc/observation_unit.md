# 관측치 단위

관측치 단위는 obsunit_t 로 표현된다. 사용되는 모든 단위는 이 문서에 등록되어야 한다. 단위를 조합하여 사용하는 것은 불가능하다.

| 이름 | 번호 | 단위 | 설명 |
|:--------|--------:|:--------:|:--------|
| OU_NONE | 1 | |  단위가 없는 무차원 값 |
| OU_CELSIUS | 2 | ℃ |  섭씨온도단위 |
| OU_FAHRENHEIT | 3 | ℉ |  화씨온도단위 |
| OU_ABSTEMP | 4 | K | 절대온도단위 |
| OU_PERCENT | 5 | % | 퍼센트 |

```
typedef enum {
    OU_NONE = 1,
    OU_CELSIUS = 2,
    OU_FAHRENHEIT = 3,
    OU_ABSTEMP = 4,
    OU_PERCENT = 5,
} devstat_t;
```
