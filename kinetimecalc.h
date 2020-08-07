#ifndef KINETIMECALC_H
#define KINETIMECALC_H

#include <iostream>
#include <cstddef>
#include <math.h>
#include <QDebug>

using namespace std;

class KineTimeCalc
{
public:
    KineTimeCalc(size_t totalLayer, size_t bedCuringLayer, float layerDelay, float layerHeight, float zOffset,
                 float minSpeed, float maxSpeed, float constUpAcc, float constUpDec, float constDownAcc, float constDownDec,
                 float bedCuringTime, float curingTime):
        _totalLayer(totalLayer), _bedCuringLayer(bedCuringLayer),
        _layerDelay(layerDelay), _layerHeight(layerHeight),
        _minSpeed(minSpeed), _maxSpeed(maxSpeed),
        _zOffset(zOffset), _constUpAcc(constUpAcc), _constUpDec(constUpDec),
        _constDownAcc(constDownAcc), _constDownDec(constDownDec),
        _bedCuringTime(bedCuringTime), _curingTime(curingTime)
    {
        _tUpAccMaxSpeed = (_maxSpeed - _minSpeed) / _constUpAcc;
        _tUpDecMaxSpeed = (_maxSpeed - _minSpeed) / _constUpDec;

        _upAccDist = 0.5f * _constUpAcc * pow(_tUpAccMaxSpeed, 2) + _minSpeed * _tUpAccMaxSpeed;
        _upDecDist = 0.5f * _constUpDec * pow(_tUpDecMaxSpeed, 2) + _minSpeed * _tUpDecMaxSpeed;

        _downAccDist = 0.5f * _constDownAcc * pow(_tDownAccMaxSpeed, 2) + _minSpeed * _tDownAccMaxSpeed;
        _downDecDist = 0.5f * _constDownDec * pow(_tDownDecMaxSpeed, 2) + _minSpeed * _tDownDecMaxSpeed;

//        _accDist = (_maxSpeed * _maxSpeed - _minSpeed * _minSpeed) / _constAcc / 2;
    }
    double moveDownTime(size_t layerCnt)
    {
//        auto dist = _zOffset + layerCnt * _layerHeight;
        auto dist = _zOffset - _layerHeight;
//        auto totalDist = layerCnt * dist;

        if(_downAccDist + _downDecDist > dist){

            auto remainDist = dist - (_downAccDist + _downDecDist);
            auto remainTime = remainDist / _maxSpeed;

            auto time = _tDownAccMaxSpeed + _tDownDecMaxSpeed + remainTime;

            return time * layerCnt;

        }else{
            auto time = KineTimeCalc::calcTRMoveTime(_maxSpeed,_minSpeed,_constDownAcc,-_constDownDec,dist);

            return time * layerCnt;
        }
    }
    double moveUpTime(size_t layerCnt)
    {
        auto dist = _zOffset;

        if(_upAccDist + _upDecDist > dist){

            auto remainDist = dist - (_upAccDist + _upDecDist);
            auto remainTime = remainDist / _maxSpeed;

            auto time = _tUpAccMaxSpeed + _tUpDecMaxSpeed + remainTime;

            return time * layerCnt;

        }else{
            auto time = KineTimeCalc::calcTRMoveTime(_maxSpeed,_minSpeed,_constUpAcc,-_constUpDec,dist);

            return time * layerCnt;
        }
    }
    /// <summary>
    /// @prevLayerCnt count of already printed layers
    /// </summary>
    int layerPrintTime()
    {
        auto sum = moveUpTime(_totalLayer);
        qDebug() << "SUM1 " << sum;
        sum += moveDownTime(_totalLayer);
        qDebug() << "SUM2 " << sum;
        //TODO: add option for bed curing
        sum += _bedCuringTime * _bedCuringLayer;
        sum += _curingTime * (_totalLayer - _bedCuringLayer);
        sum += _layerDelay * _totalLayer;

        return sum;
    }
    static double calcTRMoveTime(float maxSpeed, float minSpeed, float accelSpeed,float decelSpeed, float distance);
private:
    //all measurements in same unit of lengthlayerDelay and time
    size_t _totalLayer;
    size_t _bedCuringLayer;
    float _layerDelay;
    float _layerHeight;
    float _minSpeed;
    float _maxSpeed;
    float _zOffset;
    float _constUpAcc;
    float _constUpDec;
    float _constDownAcc;
    float _constDownDec;
    float _bedCuringTime;
    float _curingTime;
    //time to reach max speed
    float _tUpAccMaxSpeed;
    float _tUpDecMaxSpeed;
    float _tDownAccMaxSpeed;
    float _tDownDecMaxSpeed;
    //distance travelled to reach max speed
    float _upAccDist;
    float _upDecDist;
    float _downAccDist;
    float _downDecDist;
};

#endif // KINETIMECALC_H
