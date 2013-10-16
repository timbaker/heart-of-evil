Schedule
	SCHED_SOG_FREEZE
	Tasks
		TASK_WAIT_INDEFINITE           0
	Interrupts
		COND_NEW_ENEMY
		COND_ENEMY_DEAD
		COND_SOG_CAN_AMBUSH
		COND_SOG_TOUCHED_ENEMY
		COND_ENEMY_TOO_FAR
		COND_NO_PRIMARY_AMMO
		COND_LIGHT_DAMAGE
		COND_HEAVY_DAMAGE
		COND_HEAR_DANGER

Schedule
	SCHED_SOG_FADE_OUT
	Tasks
		TASK_STOP_MOVING               0
		TASK_SET_ACTIVITY              ACTIVITY:ACT_IDLE
		TASK_SOG_FADE_OUT              0
		TASK_REMEMBER                  MEMORY:CUSTOM2
		TASK_SET_SCHEDULE              SCHEDULE:SCHED_SOG_FREEZE
	Interrupts

Schedule
	SCHED_SOG_FADE_IN
	Tasks
		TASK_STOP_MOVING               0
		TASK_SOG_FADE_IN               0
		TASK_FORGET                    MEMORY:CUSTOM2
	Interrupts

Schedule
	SCHED_SOG_FADE_IN_HIT_AND_RUN
	Tasks
		TASK_STOP_MOVING               0
		TASK_SOG_FADE_IN               0
		TASK_FORGET                    MEMORY:CUSTOM2
		TASK_SET_FAIL_SCHEDULE         SCHEDULE:SCHED_TAKE_COVER_FROM_ENEMY
		TASK_FACE_ENEMY                0
		TASK_HUMAN_CHECK_FIRE          0
 TASK_SET_ACTIVITY           	ACTIVITY:ACT_IDLE_ANGRY // FIXME
 TASK_SOG_PAINT_ENEMY           0
		TASK_RANGE_ATTACK1             0
// This ignores the weapon's rate of fire
//		TASK_FACE_ENEMY                0
//		TASK_HUMAN_CHECK_FIRE          0
//		TASK_RANGE_ATTACK1             0
		TASK_SET_SCHEDULE              SCHEDULE:SCHED_TAKE_COVER_FROM_ENEMY
	Interrupts
		COND_NO_PRIMARY_AMMO
		COND_ENEMY_OCCLUDED
	COND_ENEMY_DEAD
	COND_LOST_ENEMY
	COND_NEW_ENEMY
		COND_HEAR_DANGER

Schedule
	SCHED_SOG_FADE_IN_GRENADE_AND_RUN
	Tasks
		TASK_SOG_FADE_IN               0
		TASK_FORGET                    MEMORY:CUSTOM2
		TASK_HUMAN_FACE_TOSS_DIR       0
		TASK_RANGE_ATTACK2             0
		TASK_SET_SCHEDULE              SCHEDULE:SCHED_TAKE_COVER_FROM_ENEMY
	Interrupts

Schedule
	SCHED_SOG_FADE_IN_TAKE_COVER_FROM_ENEMY
	Tasks
		TASK_SOG_FADE_IN               0
		TASK_FORGET                    MEMORY:CUSTOM2
		TASK_SET_FAIL_SCHEDULE         SCHEDULE:SCHED_SOG_FADE_IN_HIT_AND_RUN
		TASK_FIND_COVER_FROM_ENEMY     0
		TASK_HUMAN_SOUND_COVER         0.5
		TASK_RUN_PATH                  0
		TASK_WAIT_FOR_MOVEMENT         0
		TASK_REMEMBER                  MEMORY:INCOVER
		TASK_TURN_LEFT                 179
	Interrupts

Schedule
	SCHED_SOG_FADE_IN_SCRIPT
	Tasks
		TASK_SOG_FADE_IN               0
		TASK_FORGET                    MEMORY:CUSTOM2
		TASK_SET_SCHEDULE              SCHEDULE:SCHED_AISCRIPT
	Interrupts

Schedule
	SCHED_SOG_FADE_IN_COWER
	Tasks
		TASK_SOG_FADE_IN               0
		TASK_FORGET                    MEMORY:CUSTOM2
		TASK_SET_SCHEDULE              SCHEDULE:SCHED_COWER
	Interrupts

Schedule
	SCHED_SOG_FADE_IN_TAKE_COVER_FROM_BEST_SOUND
	Tasks
		TASK_SET_FAIL_SCHEDULE         SCHEDULE:SCHED_SOG_FADE_IN_COWER
		TASK_STOP_MOVING               0
		TASK_FIND_COVER_FROM_BEST_SOUND 0
		TASK_SOG_FADE_IN               0
		TASK_FORGET                    MEMORY:CUSTOM2
		TASK_SET_FAIL_SCHEDULE         SCHEDULE:SCHED_FLEE_FROM_BEST_SOUND
		TASK_HUMAN_SOUND_GRENADE       0.5
		TASK_HUMAN_CROUCH              0
		TASK_RUN_PATH                  0
		TASK_WAIT_FOR_MOVEMENT         0
		TASK_REMEMBER                  MEMORY:INCOVER
		TASK_TURN_LEFT                 179
	Interrupts

Schedule
	SCHED_SOG_FADE_IN_TAKE_COVER_FROM_ORIGIN
	Tasks
		TASK_SOG_FADE_IN               0
		TASK_FORGET                    MEMORY:CUSTOM2
		TASK_SET_SCHEDULE              SCHEDULE:SCHED_TAKE_COVER_FROM_ORIGIN
	Interrupts

Schedule
	SCHED_SOG_FADE_IN_ESTABLISH_AMBUSH_POSITION
	Tasks
		TASK_SOG_FADE_IN               0
		TASK_FORGET                    MEMORY:CUSTOM2
		TASK_SET_SCHEDULE              SCHEDULE:SCHED_SOG_ESTABLISH_AMBUSH_POSITION
	Interrupts

Schedule
	SCHED_SOG_ESTABLISH_AMBUSH_POSITION
	Tasks
		TASK_SET_FAIL_SCHEDULE         SCHEDULE:SCHED_HUMAN_ESTABLISH_LINE_OF_FIRE
		TASK_FIND_NEAR_NODE_COVER_FROM_ENEMY 2048
		TASK_RUN_PATH                  0
		TASK_WAIT_FOR_MOVEMENT         0
		TASK_SET_SCHEDULE              SCHEDULE:SCHED_SOG_FADE_OUT
	Interrupts
		COND_NEW_ENEMY
		COND_ENEMY_DEAD
		COND_LIGHT_DAMAGE
		COND_HEAVY_DAMAGE
		COND_CAN_RANGE_ATTACK1
		COND_CAN_MELEE_ATTACK1
		COND_CAN_RANGE_ATTACK2
		COND_CAN_MELEE_ATTACK2
		COND_HEAR_DANGER

