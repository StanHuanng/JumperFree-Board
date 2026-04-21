#include "bridge_manager.h"

static bridge_t bridge_table[BRIDGE_MAX_COUNT];
static rt_uint8_t bridge_used_count;

rt_bool_t bridge_is_valid_channel(rt_uint8_t x, rt_uint8_t y)
{
    return (x < BRIDGE_CH446Q_X_COUNT && y < BRIDGE_CH446Q_Y_COUNT) ? RT_TRUE : RT_FALSE;
}

void bridge_manager_init(void)
{
    bridge_manager_clear();
}

void bridge_manager_clear(void)
{
    rt_base_t level = rt_hw_interrupt_disable();

    rt_memset(bridge_table, 0, sizeof(bridge_table));
    bridge_used_count = 0;

    rt_hw_interrupt_enable(level);
}

static int bridge_find_slot(rt_uint8_t x, rt_uint8_t y)
{
    int i;

    for (i = 0; i < BRIDGE_MAX_COUNT; i++)
    {
        if (bridge_table[i].valid == RT_TRUE && bridge_table[i].x == x && bridge_table[i].y == y)
        {
            return i;
        }
    }

    return -1;
}

static int bridge_find_free_slot(void)
{
    int i;

    for (i = 0; i < BRIDGE_MAX_COUNT; i++)
    {
        if (bridge_table[i].valid != RT_TRUE)
        {
            return i;
        }
    }

    return -1;
}

rt_err_t bridge_add(rt_uint8_t x, rt_uint8_t y)
{
    int slot;
    rt_base_t level;

    if (bridge_is_valid_channel(x, y) != RT_TRUE)
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();

    if (bridge_find_slot(x, y) >= 0)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    slot = bridge_find_free_slot();
    if (slot < 0)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EFULL;
    }

    bridge_table[slot].x = x;
    bridge_table[slot].y = y;
    bridge_table[slot].valid = RT_TRUE;
    bridge_used_count++;

    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

rt_err_t bridge_remove(rt_uint8_t x, rt_uint8_t y)
{
    int slot;
    rt_base_t level;

    if (bridge_is_valid_channel(x, y) != RT_TRUE)
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();

    slot = bridge_find_slot(x, y);
    if (slot < 0)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EEMPTY;
    }

    bridge_table[slot].valid = RT_FALSE;
    bridge_table[slot].x = 0;
    bridge_table[slot].y = 0;

    if (bridge_used_count > 0)
    {
        bridge_used_count--;
    }

    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

rt_bool_t bridge_contains(rt_uint8_t x, rt_uint8_t y)
{
    rt_bool_t found;
    rt_base_t level;

    if (bridge_is_valid_channel(x, y) != RT_TRUE)
    {
        return RT_FALSE;
    }

    level = rt_hw_interrupt_disable();
    found = (bridge_find_slot(x, y) >= 0) ? RT_TRUE : RT_FALSE;
    rt_hw_interrupt_enable(level);

    return found;
}

rt_uint8_t bridge_count(void)
{
    rt_uint8_t count;
    rt_base_t level = rt_hw_interrupt_disable();

    count = bridge_used_count;

    rt_hw_interrupt_enable(level);
    return count;
}

rt_uint8_t bridge_capacity(void)
{
    return BRIDGE_MAX_COUNT;
}

rt_err_t bridge_get(rt_uint8_t index, bridge_t *bridge)
{
    rt_uint8_t visible_index = 0;
    int i;
    rt_base_t level;

    if (bridge == RT_NULL)
    {
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();

    for (i = 0; i < BRIDGE_MAX_COUNT; i++)
    {
        if (bridge_table[i].valid != RT_TRUE)
        {
            continue;
        }

        if (visible_index == index)
        {
            *bridge = bridge_table[i];
            rt_hw_interrupt_enable(level);
            return RT_EOK;
        }

        visible_index++;
    }

    rt_hw_interrupt_enable(level);
    return -RT_EEMPTY;
}
