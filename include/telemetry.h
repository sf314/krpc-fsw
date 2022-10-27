#ifndef _TELEMETRY_H

#define _TELEMETRY_H

typedef struct {
    // Position data
    double alt_mean; // ASL
    double alt_surf; // AGL
    double lat; // GPS N<->S, (-90,90)
    double lon; // GPS E<->W, (-180, 180)

    // Orientation data
    double dir_x; // Note: take from vessel in surface reference frame
    double dir_y;
    double dir_z;
    double pitch; // Note: take from vessel in vessel reference frame
    double heading;
    double roll;

    // Motion data
    double speed;
    double speed_mach;
    double speed_h;
    double speed_v;

    // Forces
    float g_force;
    float thrust;
    float thrust_avail;

    // TODO:
    // Thrust per engine
    // Gear status (up/down)
    // Light status
    // Aileron pitch
    // Elevator pitch
    // Rudder angle
    // Flaps status
    // Indicated airspeed
    // Ambient pressure
    // Mass
    // Drag (vector?)

} telemetry_t;


#endif