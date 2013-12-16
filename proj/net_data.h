#ifndef _NET_DATA_H
#define _NET_DATA_H

#include <vector>
#include <string>

#include "netmessage.pb.h"

using namespace std;

class NetData {
public:
	NetData() {}

	net::PageResult getRequestResult(net::PageRequest &pageRequest) {
		net::PageResult pageResult;

		switch (pageRequest.request_id()) {
			case 1:
			{
				net::AccountResult* accountResult = new net::AccountResult;
				pageResult.set_allocated_account_result(accountResult);
				switch (pageRequest.account_request().request_id()) {
					case 1:
						accountResult->set_user_id(1);
						accountResult->set_error_message("Register success");
						break;
					case 2:
						accountResult->set_user_id(1);
						accountResult->set_error_message("Login success");
						break;
					case 3:
						accountResult->set_user_id(1);
						accountResult->set_error_message("Password change success");
				}
				break;
			}
			case 2:
			{
				net::FoodResult* foodResult = new net::FoodResult;
				pageResult.set_allocated_food_result(foodResult);
				net::UintFloatPair* pair = foodResult->add_recipe();
				pair->set_int_value(1);
				pair->set_float_value(0.5);
				break;
			}
			case 3:
			{
				net::NutritionResult* nutritionResult = new net::NutritionResult;
				pageResult.set_allocated_nutrition_result(nutritionResult);
				switch (pageRequest.nutrition_request().request_id()) {
					case 1:
						nutritionResult->add_nutrition(12.3);
						nutritionResult->add_recommend(23.1);
						break;
					case 2:
						nutritionResult->add_nutrition(0);
						nutritionResult->add_recommend(0);
				}
				break;
			}
			case 4:
			{
				net::HealthResult* healthResult = new net::HealthResult;
				pageResult.set_allocated_health_result(healthResult);
				net::UintFloatPair* pair = healthResult->add_syndrome();
				switch (pageRequest.health_request().request_id()) {
					case 1:
						pair->set_int_value(1);
						pair->set_float_value(0.2);
						healthResult->set_analyze("Health");
						break;
					case 2:
						pair->set_int_value(2);
						pair->set_float_value(0.5);
						break;
					case 3:
						pair->set_int_value(3);
						pair->set_float_value(0.6);
						healthResult->set_symptom(1);
				}
				break;
			}
			case 5:
			{
				net::DataResult* dataResult = new net::DataResult;
				pageResult.set_allocated_data_result(dataResult);
				switch (pageRequest.data_request().request_id()) {
					case 1:
						dataResult->add_id(1);
						break;
					case 2:
						dataResult->add_id(2);
				}
			}
		}

		return pageResult;
	}

	net::PageRequest PageRequestParseFromString(std::string &buffer) {
		net::PageRequest pageRequest;
		pageRequest.ParseFromString(buffer);
		return pageRequest;
	}

	void PageResultSerialize2String(net::PageResult &pageResult, std::string &buffer) {
		pageResult.SerializeToString(&buffer);
	}

private:

};

#endif
