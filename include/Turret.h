#ifndef TURRET_H
#define TURRET_H

#include "cocos2d.h"
#include "Displayable.h"
#include "Container.h"


using namespace cocos2d;

class Turret : public CCSprite
{
	public:
		Turret();
		Turret(float rotation, const char * filename, Game * game, Layer * layer, float x_relative, float y_relative, float missile_speed, const char * missile_filename, int damage, float cooldown, float range_max, Unit * shooter_unit);
		virtual ~Turret();
		//~Turret(); //Besoin ? => Nope
				
		// --- GET ---
		CCPoint      get_relative_position();
		float        get_missile_speed();
		const char * get_missile_filename();
		float        get_damage();
		float        get_cooldown();
		float        get_range_max();
		virtual Displayable::DisplayableType getType() { return Displayable::turretType; }
		
		//Causaient des segfault
		//Unit * get_shooter_unit();
		//Unit * get_target_unit();
		
		// --- SET ---
		void set_relative_position(float x_relative, float y_relative);
		void set_missile_speed(float missile_speed);
		void set_missile_filename(const char * missile_filename);
		void set_damage(float damage);
		void set_cooldown(float cooldown);
		void set_range_max(float range_max);
		
		//void set_shooter_unit(Unit * shooter_unit);
		//void set_target_unit(Unit * target_unit);
		
		// --- METHODES ---
		void check_attack();
		void fire();
		void update(float dt);
		
		Unit * get_unit(/*int index, */Container<Unit>& unit_list) { return unit_list.get_t(0); } //l'index devrait toujours être = 0
		void   remove_unit(Container<Unit>& unit_list); //Remove le contenu du conteneur donné
		void   change_unit(Unit * unit, Container<Unit>& unit_list);
		int    get_number_unit(Container<Unit> unit_list) { return unit_list.get_number_t(); }
		
		void   rotate_to_target();
		
	private:
		// --- Attributs ---
		float           _rotation;
		CCPoint         _relative_position;
		float           _missile_speed;
		char *    _missile_filename;		
		float           _damage;	
		float           _current_cooldown; //temps écoulé depuis le dernier tir. Si il vaut cooldown, il ne s'incrémente plus et le projectile est prêt à être tiré.
		float           _cooldown;
		float           _range_max;
		Container<Unit> _shooter_unit; //L'unité qui a lancé le projectile
		Container<Unit> _target_unit;  //L'unité ciblée

};

#endif
