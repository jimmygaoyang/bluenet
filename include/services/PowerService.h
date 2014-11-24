/**
 * Author: Dominik Egger
 * Copyright: Distributed Organisms B.V. (DoBots)
 * Date: Oct 21, 2014
 * License: LGPLv3+, Apache License, or MIT, your choice
 */

#ifndef POWERSERVICE_H_
#define POWERSERVICE_H_

#include "BluetoothLE.h"
#include <util/function.h>

#include <drivers/nrf_adc.h>
#include <common/storage.h>

#define POWER_SERVICE_UUID "5b8d7800-6f20-11e4-b116-123b93f75cba"

#define PWM_UUID                                 0x1
#define VOLTAGE_CURVE_UUID                       0x2
#define POWER_CONSUMPTION_UUID                   0x3
#define CURRENT_LIMIT_UUID                       0x4

class PowerService : public BLEpp::GenericService {

public:
	typedef function<int8_t()> func_t;

protected:
	void addPWMCharacteristic();
	void addVoltageCurveCharacteristic();
	void addPowerConsumptionCharachteristic();
	void addCurrentLimitCharacteristic();

	void sampleAdcInit();
	void sampleAdcStart();

	uint16_t getCurrentLimit();

	BLEpp::Characteristic<uint16_t> *_currentLimitCharacteristic;
public:
	PowerService(BLEpp::Nrf51822BluetoothStack& stack, ADC &adc, Storage &storage);

	void addSpecificCharacteristics();

	static PowerService& createService(BLEpp::Nrf51822BluetoothStack& stack, ADC &adc, Storage &storage);
	
	void loop();
private:
	BLEpp::Nrf51822BluetoothStack* _stack;

	// We need an AD converter for this service
	ADC &_adc;

	// We need persistent storage for this service
	Storage &_storage;

	// Current limit
	uint16_t _current_limit;
};

#endif /* POWERSERVICE_H_ */