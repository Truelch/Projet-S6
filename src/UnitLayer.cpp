#include "UnitLayer.h"

#include "Unit.h"
#include <tinyxml.h>
#include "Player.h"

UnitLayer::UnitLayer(): Layer(){
}

UnitLayer::UnitLayer(Game * game): Layer(game){
}

void UnitLayer::add_unit(std::string name, float x, float y, float x_dest, float y_dest, float rotation, float move_speed, float hitboxRadius, float groundFixture, float density, const char * filename, int hp, int hp_max, int hp_regen, int power, int power_max, int power_regen, int armor, int prod_time, float sight, Player * owner) {
	Unit * unit = new Unit(name,x,y,x_dest,y_dest,rotation,move_speed,hitboxRadius,groundFixture,density,filename,get_game(),this,hp,hp_max,hp_regen,power,power_max,power_regen,armor,prod_time,sight,owner);
	_unit_list.add_t(unit);
}

bool UnitLayer::add_unit(std::string name, float x, float y, float x_dest, float y_dest, float rotation, std::string unit_type, Player * owner) {
	unsigned int i;
	char filename[100], missile_filename[100];
	sprintf(filename,_unit_catalog[unit_type].filename,owner->get_color());

	if(_unit_catalog.find(unit_type)==_unit_catalog.end()) return false;

	add_unit(name,x,y,x_dest,y_dest,rotation,
	         _unit_catalog[unit_type].move_speed,
	         _unit_catalog[unit_type].hitboxRadius,
	         _unit_catalog[unit_type].groundFixture,
	         _unit_catalog[unit_type].density,
	         filename,
	         _unit_catalog[unit_type].hp,
	         _unit_catalog[unit_type].hp_max,
	         _unit_catalog[unit_type].hp_regen,
	         _unit_catalog[unit_type].power,
	         _unit_catalog[unit_type].power_max,
	         _unit_catalog[unit_type].power_regen,
	         _unit_catalog[unit_type].armor,
	         _unit_catalog[unit_type].prod_time,
	         _unit_catalog[unit_type].sight,
			 owner);

	for(i=0;i<_unit_catalog[unit_type].turret_list.size();i++) {
		sprintf(filename,_unit_catalog[unit_type].turret_list[i].filename,owner->get_color());
		sprintf(missile_filename,_unit_catalog[unit_type].turret_list[i].missile_filename,owner->get_color());
		_unit_list.get_t(_unit_list.get_number_t()-1)->add_turret(
			_unit_catalog[unit_type].turret_list[i].rotation,
			filename,
			get_game(),
			this,
			_unit_catalog[unit_type].turret_list[i].x_relative,
			_unit_catalog[unit_type].turret_list[i].y_relative,
			_unit_catalog[unit_type].turret_list[i].missile_speed,
			missile_filename,
			_unit_catalog[unit_type].turret_list[i].damage,
			_unit_catalog[unit_type].turret_list[i].cooldown,
			_unit_catalog[unit_type].turret_list[i].range_max,
			_unit_list.get_t(_unit_list.get_number_t()-1));
	}

	return true;
}

void UnitLayer::remove_unit(Unit * unit) {
	_unit_list.remove_t(unit);
}

char UnitLayer::init_unit_catalog(std::string filename) {
	TiXmlDocument doc(filename);
	TiXmlHandle docHandle(&doc);
	int i,j,k, intValue;
	float floatValue;
	const char * name;
	const char * unit_type;

	if(!doc.LoadFile()) return EXIT_FAILURE;
	if(!docHandle.FirstChild("units").ToElement()) return EXIT_FAILURE;

	i=-1;
	while(true) {
		i++;
		if(!docHandle.FirstChild("units").Child("unit",i).ToElement()) break;
		if(!docHandle.FirstChild("units").Child("unit",i).ToElement()->Attribute("name")) continue;

		unit_type = docHandle.FirstChild("units").Child("unit",i).ToElement()->Attribute("name");
		_unit_catalog[unit_type] = {4.0f,22.4f,5.0f,1.0f,(char*)malloc(100),200,200,1,100,100,1,6,100,400.0f,vector<TurretStat>()};
		_unit_catalog[unit_type].filename[0]='\0';

		j=-1;
		while(true) {
			j++;
			if(!docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()) break;
			if(!(name=docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->Attribute("name"))) continue;
			if(!docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->Attribute("value")) continue;

			if(strcmp(name,"move_speed")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryFloatAttribute("value",&floatValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].move_speed = floatValue;
				}
			}
			else if(strcmp(name,"hitboxRadius")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryFloatAttribute("value",&floatValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].hitboxRadius = floatValue;
				}
			}
			else if(strcmp(name,"groundFixture")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryFloatAttribute("value",&floatValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].groundFixture = floatValue;
				}
			}
			else if(strcmp(name,"density")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryFloatAttribute("value",&floatValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].density = floatValue;
				}
			}
			else if(strcmp(name,"filename")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->Attribute("value"))
					strcpy(_unit_catalog[unit_type].filename,docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->Attribute("value"));
			}
			else if(strcmp(name,"hp")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryIntAttribute("value",&intValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].hp = intValue;
				}
			}
			else if(strcmp(name,"hp_max")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryIntAttribute("value",&intValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].hp_max = intValue;
				}
			}
			else if(strcmp(name,"hp_regen")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryIntAttribute("value",&intValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].hp_regen = intValue;
				}
			}
			else if(strcmp(name,"power")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryIntAttribute("value",&intValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].power = intValue;
				}
			}
			else if(strcmp(name,"power_max")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryIntAttribute("value",&intValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].power_max = intValue;
				}
			}
			else if(strcmp(name,"power_regen")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryIntAttribute("value",&intValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].power_regen = intValue;
				}
			}
			else if(strcmp(name,"armor")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryIntAttribute("value",&intValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].armor = intValue;
				}
			}
			else if(strcmp(name,"prod_time")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryIntAttribute("value",&intValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].prod_time = intValue;
				}
			}
			else if(strcmp(name,"sight")==0) {
				if(docHandle.FirstChild("units").Child("unit",i).Child("property",j).ToElement()->QueryFloatAttribute("value",&floatValue)==TIXML_SUCCESS) {
					_unit_catalog[unit_type].sight = floatValue;
				}
			}
		}

		if(!docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").ToElement()) continue;

		j=-1;
		while(true) {
			j++;
			if(!docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).ToElement()) break;
			_unit_catalog[unit_type].turret_list.push_back({0,(char*)malloc(100),3.0,8.0,75.0,(char*)malloc(100),30,1.5,250.0});
			(_unit_catalog[unit_type].turret_list.end()-1)->filename[0]='\0';
			(_unit_catalog[unit_type].turret_list.end()-1)->missile_filename[0]='\0';

			k=-1;
			while(true) {
				k++;
				if(!docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()) break;
				if(!(name=docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->Attribute("name"))) continue;
				if(!docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->Attribute("value")) continue;

				if(strcmp(name,"rotation")==0) {
					if(docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->QueryFloatAttribute("value",&floatValue)==TIXML_SUCCESS) {
						(_unit_catalog[unit_type].turret_list.end()-1)->rotation = floatValue;
					}
				}
				else if(strcmp(name,"filename")==0) {
					if(!docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->Attribute("filename")) {
						strcpy((_unit_catalog[unit_type].turret_list.end()-1)->filename,docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->Attribute("value"));
					}
				}
				else if(strcmp(name,"x_relative")==0) {
					if(docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->QueryFloatAttribute("value",&floatValue)==TIXML_SUCCESS) {
						(_unit_catalog[unit_type].turret_list.end()-1)->x_relative = floatValue;
					}
				}
				else if(strcmp(name,"y_relative")==0) {
					if(docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->QueryFloatAttribute("value",&floatValue)==TIXML_SUCCESS) {
						(_unit_catalog[unit_type].turret_list.end()-1)->y_relative = floatValue;
					}
				}
				else if(strcmp(name,"missile_speed")==0) {
					if(docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->QueryFloatAttribute("value",&floatValue)==TIXML_SUCCESS) {
						(_unit_catalog[unit_type].turret_list.end()-1)->missile_speed = floatValue;
					}
				}
				else if(strcmp(name,"missile_filename")==0) {
					if(docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->Attribute("value")) {
						strcpy((_unit_catalog[unit_type].turret_list.end()-1)->missile_filename,docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->Attribute("value"));
					}
				}
				else if(strcmp(name,"damage")==0) {
					if(docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->QueryIntAttribute("value",&intValue)==TIXML_SUCCESS) {
						(_unit_catalog[unit_type].turret_list.end()-1)->damage = intValue;
					}
				}
				else if(strcmp(name,"cooldown")==0) {
					if(docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->QueryFloatAttribute("value",&floatValue)==TIXML_SUCCESS) {
						(_unit_catalog[unit_type].turret_list.end()-1)->cooldown = floatValue;
					}
				}
				else if(strcmp(name,"range_max")==0) {
					if(docHandle.FirstChild("units").Child("unit",i).FirstChild("turrets").Child("turret",j).Child("property",k).ToElement()->QueryFloatAttribute("value",&floatValue)==TIXML_SUCCESS) {
						(_unit_catalog[unit_type].turret_list.end()-1)->range_max = floatValue;
					}
				}
			}
		}
	}

	return EXIT_SUCCESS;
}

