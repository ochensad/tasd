#include "task_simulation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

elem_t create_task(int type)
{
    elem_t el;
    el.type = type;
    if (type == 1)
        el.time = (T1_END - T1_START) *(double) rand()/RAND_MAX + T1_START;
    else if (type == 2)
        el.time = (T2_END - T2_START) * (double) rand()/ RAND_MAX + T2_START;
    return el;
}

void fill_turn_first(list_turn_t *turn)
{
    elem_t el;
    for (int i = 0; i < TURN_LEN; i++)
    {
        el = create_task(1);
        push_turn_list(turn, el, TURN_LEN);
    }
}

void fill_arr_first(array_turn_t *turn)
{
    elem_t el;
    for (int i = 0; i < TURN_LEN; i++)
    {
        el = create_task(1);
        push_turn_array(turn, el);
    }
}

void push_el_bcs_probility(list_turn_t *first, list_turn_t *second)
{
    int p = rand() % 100;
    elem_t el;
    if (p <= P_2)
    {
        el = create_task(2);
        push_turn_list(second, el, TURN_LEN);
    }
    else if (p > P_2)
    {
        el = create_task(1);
        push_turn_list(first, el, TURN_LEN);
    }
}

void push_arr_el_bcs_prob(array_turn_t *f, array_turn_t *s)
{
    int p = rand() % 100;
    elem_t el;
    if (p <= P_2)
    {
        el = create_task(2);
        push_turn_array(s, el);
    }
    else if (p > P_2)
    {
        el = create_task(1);
        push_turn_array(f, el);
    }
}

void check_hundred_task(int oa_2_out, list_turn_t *t_1, list_turn_t *t_2, int avglen_1, int avglen_2, int oa_1_out)
{
    if (oa_2_out % 100 == 0)
    {
        int p = rand() % 100;
        int f = 0, s = 0;
        if (p < P_2)
            s = 1;
        else
            f = 1;

        printf("\nОА2 обработал %d заявок\n"
                "Длина очереди 1: %zu\n"
                "Средняя длина очереди 1: %d\n"
                "Длина очереди 2: %zu\n"
                "Средняя длина очереди 2: %d\n\n",
                oa_2_out, t_1->size + f, avglen_1 / oa_1_out, t_2->size + s, avglen_2 / oa_2_out);
    }
}

void check_hundred_arr_task(int oa_2_out, array_turn_t *t_1, array_turn_t *t_2, int avglen_1, int avglen_2, int oa_1_out)
{
    if (oa_2_out % 100 == 0)
    {
        int p = rand() % 100;
        int f = 0, s = 0;
        if (p < P_2)
            s = 1;
        else
            f = 1;

        printf("\nОА2 обработал %d заявок\n"
                "Длина очереди 1: %d\n"
                "Средняя длина очереди 1: %d\n"
                "Длина очереди 2: %d\n"
                "Средняя длина очереди 2: %d\n\n",
                oa_2_out, t_1->size + f, avglen_1 / oa_1_out, t_2->size + s, avglen_2 / oa_2_out);
    }
}

void arr_simulation(void)
{
    array_turn_t turn_1;
    array_turn_t turn_2;

    turn_1.size = 0;
    turn_1.max_size = 100;
    turn_1.arr = malloc(sizeof(elem_t) * turn_1.max_size);
    turn_1.head = turn_1.arr;
    turn_1.tail = turn_1.arr;
    fill_arr_first(&turn_1);

    turn_2.size = 0;
    turn_2.max_size = 100;
    turn_2.arr = malloc(sizeof(elem_t) * turn_2.max_size);
    turn_2.head = turn_2.arr;
    turn_2.tail = turn_2.arr;

    int oa_2_out = 0, oa_1_out = 0;

    double oa_1_time = 0, oa_1_el_time = 0, oa_1_hold_time = 0;
    double oa_2_time = 0, oa_2_hold_time = 0, oa_2_el_time = 0;
    int avg_len_1 = 0, avg_len_2 = 0;

    elem_t el_turn_1, el_turn_2;

    while (oa_2_out < REQUEST_LEN)
    {
        avg_len_1 += turn_1.size;

        if (turn_1.size == 0)
        {
            pop_turn_array(&turn_2, &el_turn_2);
            oa_2_out++;
            oa_2_time += el_turn_2.time;
            oa_2_el_time = el_turn_2.time;
            oa_1_hold_time += el_turn_2.time;
            push_arr_el_bcs_prob(&turn_1, &turn_2);
            continue;
        }
        else
        {
            pop_turn_array(&turn_1, &el_turn_1);
            oa_1_out++;
            oa_1_time += el_turn_1.time;
            oa_1_el_time = el_turn_1.time;
        }

        if (turn_2.size == 0)
        {
            oa_2_hold_time += el_turn_1.time;
            push_arr_el_bcs_prob(&turn_1, &turn_2);
            continue;
        }
        oa_2_el_time = turn_2.tail->time;

        if (oa_1_el_time >= oa_2_el_time)
        {
            while (oa_1_el_time > 0)
            {
                if (oa_1_el_time >= oa_2_el_time)
                {
                    oa_1_el_time -= oa_2_el_time;
                    avg_len_2 += turn_2.size;
                    oa_2_time += turn_2.tail->time;

                    pop_turn_array(&turn_2, &el_turn_2);
                    oa_2_out++;

                    elem_t el = create_task(1);
                    push_turn_array(&turn_1, el);
                    check_hundred_arr_task(oa_2_out, &turn_1, &turn_2, avg_len_1, avg_len_2, oa_1_out);

                    if (turn_2.size == 0)
                    {
                        oa_2_hold_time += oa_1_el_time;
                        push_arr_el_bcs_prob(&turn_1, &turn_2);
                        break;
                    }
                    oa_2_el_time = turn_2.tail->time;
                }
                else
                {
                    oa_2_time += oa_1_el_time;
                    turn_2.tail->time -= oa_1_el_time;
                    push_arr_el_bcs_prob(&turn_1, &turn_2);
                    break;
                }
            }
        }
        else if (oa_1_el_time < oa_2_el_time)
        {
            oa_2_time += oa_1_el_time;
            turn_2.tail->time -= oa_1_el_time;
            push_arr_el_bcs_prob(&turn_1, &turn_2);
        }

    }

    double t_2 = ((double)(T2_END - T2_START) / 2 + T2_START) * 1000.0;
    double t_1 = ((double)(T1_END - T1_START) / 2 + T1_START) * (1000.0 * (100.0 / P_2));
    int  p = 1000.0 * (100.0 / P_2);
    printf("Рабочее время ОА1 : %lf (ожидаемое: %lf, погрешность: %lf%%)\n"
            "Рабочее время ОА2 : %lf (ожидаемое: %lf, погрешность: %lf%%)\n"
            "Количество срабатываний ОА1 : %d (ожидаемое: %d)\n"
            "Время простоя ОА2 : %lf\n"
            "Теоретическое время простоя: %lf\n"
            "Время простоя ОА1 : %lf\n",
            oa_1_time, t_1, fabs(oa_1_time - t_1) / 100,
            oa_2_time, t_2, fabs(oa_2_time - t_2) / 100,
            oa_1_out, p,
            oa_2_hold_time,
            t_1 - t_2, oa_1_hold_time);
}

void task_simulation(void)
{
    printf("\nВыберете тип очереди для моделирования:"
        "\n1 - список"
        "\n2 - массив\n");
    
    int comand = 0;
    if (scanf("%d", &comand) != 1 || comand < 1 || comand > 2)
    {
        printf("Ошибка чтения\n");
        return;
    }
    if (comand == 1)
        list_simulation();
    if (comand == 2)
        arr_simulation();
}

void list_simulation(void)
{
    list_turn_t turn_1;
    list_turn_t turn_2;

    turn_1.size = 0;
    turn_1.head = NULL;
    turn_1.tail = NULL;
    fill_turn_first(&turn_1);

    turn_2.size = 0;
    turn_2.head = NULL;
    turn_2.tail = NULL;

    int oa_2_out = 0, oa_1_out = 0;

    double oa_1_time = 0, oa_1_el_time = 0, oa_1_hold_time = 0;
    double oa_2_time = 0, oa_2_hold_time = 0, oa_2_el_time = 0;
    int avg_len_1 = 0, avg_len_2 = 0;

    elem_t el_turn_1, el_turn_2;

    while (oa_2_out < REQUEST_LEN)
    {
        avg_len_1 += turn_1.size;

        if (turn_1.size == 0 && turn_2.size != 0)
        {
            pop_turn_list(&turn_2, &el_turn_2);
            oa_2_out++;
            oa_2_time += el_turn_2.time;
            oa_2_el_time = el_turn_2.time;
            oa_1_hold_time += el_turn_2.time;
            push_el_bcs_probility(&turn_1, &turn_2);
            continue;
        }
        else if (turn_1.size)
        {
            pop_turn_list(&turn_1, &el_turn_1);
            oa_1_out++;
            oa_1_time += el_turn_1.time;
            oa_1_el_time = el_turn_1.time;
        }

        if (turn_2.size == 0)
        {
            oa_2_hold_time += el_turn_1.time;
            push_el_bcs_probility(&turn_1, &turn_2);
            continue;
        }
        oa_2_el_time = turn_2.head->data.time;

        if (oa_1_el_time >= oa_2_el_time)
        {
            while (oa_1_el_time > 0)
            {
                if (oa_1_el_time >= oa_2_el_time)
                {
                    oa_1_el_time -= oa_2_el_time;
                    avg_len_2 += turn_2.size;
                    oa_2_time += turn_2.head->data.time;

                    pop_turn_list(&turn_2, &el_turn_2);
                    oa_2_out++;

                    elem_t el = create_task(1);
                    push_turn_list(&turn_1, el, TURN_LEN);
                    check_hundred_task(oa_2_out, &turn_1, &turn_2, avg_len_1, avg_len_2, oa_1_out);

                    if (turn_2.size == 0)
                    {
                        oa_2_hold_time += oa_1_el_time;
                        push_el_bcs_probility(&turn_1, &turn_2);
                        break;
                    }
                    oa_2_el_time = turn_2.head->data.time;
                }
                else
                {
                    oa_2_time += oa_1_el_time;
                    turn_2.head->data.time -= oa_1_el_time;
                    push_el_bcs_probility(&turn_1, &turn_2);
                    break;
                }
            }
        }
        else if (oa_1_el_time < oa_2_el_time)
        {
            oa_2_time += oa_1_el_time;
            turn_2.head->data.time -= oa_1_el_time;
            push_el_bcs_probility(&turn_1, &turn_2);
        }

    }
    double t_2 = ((double)(T2_END - T2_START) / 2 + T2_START) * 1000.0;
    double t_1 = ((double)(T1_END - T1_START) / 2 + T1_START) * (1000.0 * (100.0 / P_2));
    int  p = 1000.0 * (100.0 / P_2);
    printf("Рабочее время ОА1 : %lf (ожидаемое: %lf, погрешность: %lf%%)\n"
            "Рабочее время ОА2 : %lf (ожидаемое: %lf, погрешность: %lf%%)\n"
            "Количество срабатываний ОА1 : %d (ожидаемое: %d)\n"
            "Время простоя ОА2 : %lf\n"
            "Теоретическое время простоя: %lf\n"
            "Время простоя ОА1 : %lf\n",
            oa_1_time, t_1, fabs(oa_1_time - t_1) / 100,
            oa_2_time, t_2, fabs(oa_2_time - t_2) / 100,
            oa_1_out, p,
            oa_2_hold_time,
            t_1 - t_2, oa_1_hold_time);
}