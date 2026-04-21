#ifndef BRIDGE_MANAGER_H
#define BRIDGE_MANAGER_H

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BRIDGE_MAX_COUNT 16
#define BRIDGE_CH446Q_X_COUNT 16
#define BRIDGE_CH446Q_Y_COUNT 8

typedef struct
{
    rt_uint8_t x;
    rt_uint8_t y;
    rt_bool_t valid;
} bridge_t;

void bridge_manager_init(void);
void bridge_manager_clear(void);

rt_err_t bridge_add(rt_uint8_t x, rt_uint8_t y);
rt_err_t bridge_remove(rt_uint8_t x, rt_uint8_t y);
void bridge_apply_all(void);
rt_bool_t bridge_contains(rt_uint8_t x, rt_uint8_t y);

rt_uint8_t bridge_count(void);
rt_uint8_t bridge_capacity(void);
rt_err_t bridge_get(rt_uint8_t index, bridge_t *bridge);
rt_bool_t bridge_is_valid_channel(rt_uint8_t x, rt_uint8_t y);

#ifdef __cplusplus
}
#endif

#endif /* BRIDGE_MANAGER_H */
