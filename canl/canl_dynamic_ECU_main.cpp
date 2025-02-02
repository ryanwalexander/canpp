/*
* The MIT License (MIT)
*
* Copyright(c) 2016 Thomas Dahlmann <tomydahl@gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this softwareand associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright noticeand this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*/
#include "canllib.h"

void onAllMessages(message &m);
void onStart();
void onStop();
extern Timer* g_timerArray[];
extern CanlConfig g_canlConfig;
extern Timer myTimer;
extern MsTimer myMsTimer;

RadarControl rxMsg_RadarControl;
BatteryUsage rxMsg_BatteryUsage;

/* RadarControl (0x64) */
void msgRxFunc_RadarControl(CanlMessage *rxMsg)
{
    rxMsg_RadarControl.rxFunc(rxMsg);
    rxMsg_RadarControl.onMessage();
    rxMsg_RadarControl.saveBytes();
}

/* BatteryUsage (0xc8) */
void msgRxFunc_BatteryUsage(CanlMessage *rxMsg)
{
    rxMsg_BatteryUsage.rxFunc(rxMsg);
    rxMsg_BatteryUsage.onMessage();
    rxMsg_BatteryUsage.saveBytes();
}

void msgRxInit(void)
{
    int ix = 0;

    /* RadarControl (0x64) */
    canRxArray[ix].canId = 0x64;
    canRxArray[ix].msgRxFunc = msgRxFunc_RadarControl;
    ix++;

    /* BatteryUsage (0xc8) */
    canRxArray[ix].canId = 0xc8;
    canRxArray[ix].msgRxFunc = msgRxFunc_BatteryUsage;
    ix++;

    OnStartFunc = onStart;
    OnStopFunc = onStop;
    msgRxFuncAll = onAllMessages;

    g_canlConfig.timerUsed = 1;
    g_canlConfig.numTimers = 2;
    g_timerArray[0] = &myTimer;
    g_timerArray[1] = &myMsTimer;

    canNumberMsgs = ix;
}