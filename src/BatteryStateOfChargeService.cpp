/** 
 *  University of Calgary Solar Car Team New Recruit Exercise
 *  Copyright (C) 2015 University of Calgary Solar Car Team
 *
 *  This file is part of the 
 *  University of Calgary Solar Car Team New Recruit Exercise
 *
 *  The University of Calgary Solar Car Team New Recruit Exercise 
 *  is free software: you can redistribute it and/or modify it 
 *  under the terms of the GNU General Public License as 
 *  published by the Free Software Foundation, either version 3 
 *  of the License, or (at your option) any later version.
 *
 *  The University of Calgary Solar Car Team New Recruit Exercise 
 *  is distributed in the hope that it will be useful, but WITHOUT 
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General 
 *  Public License for more details.
 *
 *  You should have received a copy of the GNU General 
 *  Public License along with the University of Calgary Solar Car 
 *  Team New Recruit Exercise. If not, see 
 *  <http://www.gnu.org/licenses/>.
 *
 *  For further contact, email <software@calgarysolarcar.ca>
 */

#include "BatteryStateOfChargeService.h"
#include <QTime>
#include <BatteryData.h>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double CONVERT_TO_MILLISECONDS = 2.7778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), prevCurrent_(0)
{
    AmpHours_ = BATTERY_AMP_HOUR_CAPACITY*(initialStateOfChargePercent_/100);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY-AmpHours_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (existingCurrent_ < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double timeRemaining = (BATTERY_AMP_HOUR_CAPACITY-AmpHours_) / prevCurrent_;
    timeRemaining = qAbs(timeRemaining) / CONVERT_TO_MILLISECONDS;
    return QTime(0, 0, 0, 0).addMSecs(timeRemaining);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    //Time Calculations
    QTime currentTime_ = batteryData.time;
    changeTime_ = abs(prevTime_.msecsTo(currentTime_));
    changeTime_ = changeTime_ * CONVERT_TO_MILLISECONDS;
    prevTime_ = currentTime_;
    dTime_ = prevTime_.msecsTo(currentTime_);
    dTime_ = dTime_ * CONVERT_TO_MILLISECONDS;

    //Current Calculations
    prevCurrent_ = existingCurrent_;
    existingCurrent_ = batteryData.current;
    AvgCurrent_ = (prevCurrent_ + existingCurrent_)/2;

    //Amp Calculations
    double AmpChange = (AvgCurrent_ * changeTime_);
    AmpHours_ += AmpChange;
}
