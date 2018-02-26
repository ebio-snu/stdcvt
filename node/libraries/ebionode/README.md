# ebiolab : Temporal library for a node

## Introduction

아두이노 기반의 샘플 노드를 개발하기위한 라이브러리이다.

## Maintainers

* 김준용 (tombraid@snu.ac.kr)

##  구조

* node.h : EbioNode 클래스를 다룬다. 3가지 종류(센서컨트롤러, 모터컨트롤러, 스위치컨트롤러)의 컨트롤러를 가지고 있다.
* controller.h : Controller 클래스는 추상 클래스로 이를 상속한 SensorObserver, MotorController, SwitchController 가 있다.
* util.h : 간단한 유틸리티를 다룬다.

## 프로토콜

[샘플노드 프로토콜](../../../doc/samplenode_protocol.md) 를 참고한다.

