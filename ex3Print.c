#include <stdio.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include <malloc.h>
#include <stdlib.h>
#include "mtm_ex3.h"
#include "EscapeTechnion.h"

void printCompany(FILE * file, Company company)
{
    fprintf(file,"email: %s faculty: %d\n",company->email, company->faculty);
    return;
}

void printRoom(FILE * file, Room room)
{
    fprintf(file,"faculty: %d id: %d email: %s price: %d num_ppl: %d "
                    "start_hour: %d stop_hour: %d difficulty: %d\n",
            room->faculty,
            room->id, room->email, room->price, room->num_ppl,
            room->start_hour, room->stop_hour, room->difficulty);
    return;
}

void printEscaper(FILE * file, Escaper escaper)
{
    fprintf(file, "email: %s faculty: %d skill_level: %d\n", escaper->email,
            escaper->faculty,
            escaper->skill_level);
    return;
}

void printOrder(FILE * file, Order order)
{
    fprintf(file, "faculty: %d room_id: %d days_to_order: %d hour: %d"
                    " num_of_people: %d\n",
            order->faculty, order->room_id,
            order->days_to_order, order->hour, order->num_of_people);
    printEscaper(file, order->escaper);
    return;
}

void printCompanySet(FILE * file, Set mtmCompanySet)
{
    int i=0;
    SET_FOREACH(Company, company, mtmCompanySet) {
        fprintf(file,"company %d:", i);
        i++;
        printCompany(file,company);
    }
    return;
}
void printRoomSet(FILE * file, Set mtmRoomSet)
{
    int i=0;
    SET_FOREACH(Room, room, mtmRoomSet) {
        fprintf(file,"room %d:", i);
        i++;
        printRoom(file, room);
    }
    return;
}
void printEscaperSet(FILE * file, Set mtmEscaperSet)
{
    int i=0;
    SET_FOREACH(Escaper, escaper, mtmEscaperSet) {
        fprintf(file,"escaper %d:", i);
        i++;
        printEscaper(file,escaper);
    }
    return;
}
void printOrderList(FILE * file, List mtmOrderList)
{
    int i=0;
    LIST_FOREACH(Order, order, mtmOrderList) {
        fprintf(file,"order %d:", i);
        i++;
        printOrder(file,order);
    }
    return;
}