# samplenode

## Introduction

컨버터 테스트를 위한 아두이노 기반의 샘플 노드이다.

## Maintainers

* 김준용 (tombraid@snu.ac.kr)

## How to use

1.  현재디렉토리를 arduino의 sketchbook location 으로 설정한다. (File->Preferences)
1. Library Manager 를 이용하여 DallasTemperature와 LiquidCrystal I2C를 설치한다.
1. samplenode.ino를 열어서 컴파일하고 업로드 한다. 

## 디폴트 설정

* DEFAULT_TERM 을 이용하여 정보전송주기를 설정할 수 있다. 디폴트는 10*1000 (10초)이다.

## 샘플노드의 프로토콜

[샘플노드 프로토콜](../doc/samplenode_protocol.md) 문서를 참고한다.

## 기타
디버그시 아래의 정의를 활성화하고,  시리얼 모니터를 사용할 수 있다.
```
#define _DEBUG_ 
```


