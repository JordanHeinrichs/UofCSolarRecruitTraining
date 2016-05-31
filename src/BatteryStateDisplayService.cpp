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
#include <QDebug>
#include <QTextStream>
#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include "BatteryStateDisplayService.h"
#include "I_BatteryDataSource.h"
#include "I_BatteryStateOfChargeService.h"
BatteryStateDisplayService::BatteryStateDisplayService(
    const I_BatteryDataSource& batteryDataSource,
    I_BatteryStateOfChargeService& batteryStateOfChargeService)
: batteryStateOfChargeService_(batteryStateOfChargeService)
{
    // This function is what "connects" the signal to the slot. So whenever the
    // signals it emitted, the slot will be called and the signal arguements
    // will be passed into the slot.
    connect(&batteryDataSource, SIGNAL(batteryDataReceived(const BatteryData&)),
        this, SLOT(handleBatteryDataReceived(const BatteryData&)));
}

BatteryStateDisplayService::~BatteryStateDisplayService()
{
}

void BatteryStateDisplayService::handleBatteryDataReceived(const BatteryData& batteryData)
{
    batteryStateOfChargeService_.addData(batteryData);
    batteryStateOfChargeService_.isCharging();
    QString voltage = QString::number(batteryData.voltage,'f',6);
    QString current = QString::number(batteryData.current,'f',6);
    QString Amp = QString::number(batteryStateOfChargeService_.totalAmpHoursUsed(),'f',2);
    if (batteryStateOfChargeService_.isCharging() != false)
    {
        QTextStream(stdout) << "Voltage: " << voltage
        << "    Current: " << current
        << "    Total Ah used:  " << Amp
        << "    Time until fully charged: " << batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString() << endl;
    }
    else
    {
        QTextStream(stdout) << "Voltage: " << voltage
        << "    Current: " << current
        << "    Total Ah used:  " << Amp
        << "    Time until fully depleted: " << batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString() << endl;
    }
}
