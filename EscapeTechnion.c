#include <stdio.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include <malloc.h>
#include <math.h>
#include "mtm_ex3.h"
#include "EscapeTechnion.h"
#include <assert.h>

static Set mtmCompanySet;
static Set mtmRoomSet;
static Set mtmEscaperSet;
static List mtmOrderList;
static List mtmFacultyList;
static int DAY_NUMBER;
static FILE *OUTPUT_FILE;

static Escaper ESCAPER_FOR_RECOMANDED_ORDERING;
static int NUM_OF_ORDERING_PEOPLE;

static SetElement mtmCopyCompany(SetElement company){
    if(!company)
        return NULL;
    Company old_company = (Company)company;
    Company new_company = malloc(sizeof(*new_company));
    new_company->email = malloc((strlen(old_company->email)+1)* sizeof(char));
    strcpy(new_company->email,old_company->email);
    new_company->faculty = old_company->faculty;
    return (SetElement)new_company;
}

static void mtmFreeCompany(SetElement company)
{
    if(!company)
        return;
    Company free_company = company;
    free(free_company->email);
    free(free_company);
}

static int mtmCompareCompany (SetElement company1_in,SetElement company2_in)
{
    Company company1 = company1_in;
    Company company2 = company2_in;
    return strcmp(company1->email,company2->email);
}

static SetElement mtmCopyRoom(SetElement room)
{
    if(!room)
        return NULL;
    Room old_room = room;
    Room new_room = malloc(sizeof(*new_room));
    new_room->email = malloc((strlen(old_room->email)+1)* sizeof(char));
    strcpy(new_room->email,old_room->email);
    new_room->faculty = old_room->faculty;
    new_room->id = old_room->id;
    new_room->price = old_room->price;
    new_room->num_ppl = old_room->num_ppl;
    new_room->start_hour = old_room->start_hour;
    new_room->stop_hour = old_room->stop_hour;
    new_room->difficulty = old_room->difficulty;
    return (SetElement)new_room;
}

static void mtmFreeRoom(SetElement room)
{
    if(!room)
        return;
    free(((Room)room)->email);
    free(((Room)room));
}

static int mtmCompareRoom(SetElement room1_in,SetElement room2_in)
{
    Room room1 = room1_in;
    Room room2 = room2_in;
    assert(room1->id>0 && room2->id>0);
    if(room1->faculty-room2->faculty != 0)
        return room1->faculty - room2->faculty;
    else
        return room1->id - room2->id;
}

static SetElement mtmCopyOrder(SetElement order)
{
    if(!order)
        return NULL;
    Order old_order = order;
    Order new_order = malloc(sizeof(*new_order));
    new_order->escaper = old_order->escaper;
    new_order->faculty = old_order->faculty;
    new_order->room_id = old_order->room_id;
    new_order->days_to_order = old_order->days_to_order;
    new_order->hour = old_order->hour;
    new_order->num_of_people = old_order->num_of_people;
    return (SetElement)new_order;
}

static void mtmFreeOrder(SetElement order)
{
    if(!order)
        return;
    free((Order)order);
}

static int mtmCompareOrder(SetElement order1,SetElement order2)
{
    Order order1_casted = order1;
    Order order2_casted = order2;
    int compare_days =
            order1_casted->days_to_order - order2_casted->days_to_order;
    int compare_hour = order1_casted->hour - order2_casted->hour;
    int compare_faculty = order1_casted->faculty - order2_casted->faculty;
    int compare_room_id = order1_casted->room_id - order2_casted->room_id;
    if        (compare_days!=0)
        return compare_days;
    else if   (compare_hour!=0)
        return compare_hour;
    else if   (compare_faculty!=0)
        return compare_faculty;
    else
        return compare_room_id;
}

static SetElement mtmCopyEscaper(SetElement escaper)
{
    if(!escaper)
        return NULL;
    Escaper old_escaper = escaper;
    Escaper new_escaper = malloc(sizeof(*new_escaper));
    new_escaper->email = malloc((strlen(old_escaper->email)+1)* sizeof(char));
    strcpy(new_escaper->email,old_escaper->email);
    new_escaper->faculty = old_escaper->faculty;
    new_escaper->skill_level = old_escaper->skill_level;
    return (SetElement)new_escaper;
}

static void mtmFreeEscaper (SetElement escaper)
{
    if(!escaper)
        return;
    free(((Escaper)escaper)->email);
    free((Escaper)escaper);
}

static int mtmCompareEscaper (SetElement escaper1_in,SetElement escaper2_in)
{
    Escaper escaper1 = escaper1_in;
    Escaper escaper2 = escaper2_in;
    return strcmp(escaper1->email,escaper2->email);
}

ListElement mtmCopyFaculty(ListElement faculty_in){
    if(!faculty_in)
        return NULL;
    Faculty faculty = faculty_in;
    Faculty new_faculty = malloc(sizeof(*new_faculty));
    new_faculty->id = faculty->id;
    new_faculty->total_income = faculty->total_income;
    return new_faculty;
}

void mtmFreeFaculty(ListElement faculty_in){
    if(!faculty_in)
        return;
    Faculty faculty = faculty_in;
    free(faculty);
}

int mtmCompareFaculty(ListElement faculty_in1,ListElement faculty_in2){
    Faculty faculty1 = faculty_in1;
    Faculty faculty2 = faculty_in2;
    if((faculty2->total_income-faculty1->total_income)!=0)
        return faculty2->total_income-faculty1->total_income;
    else
        return faculty1->id-faculty2->id;
}

void mtmInitiateEscapeTechnion(FILE* output_file)
{
    DAY_NUMBER = 0;
    mtmCompanySet = setCreate(mtmCopyCompany,mtmFreeCompany,mtmCompareCompany);
    mtmRoomSet = setCreate(mtmCopyRoom,mtmFreeRoom,mtmCompareRoom);
    mtmEscaperSet = setCreate(mtmCopyEscaper,mtmFreeEscaper,mtmCompareEscaper);
    mtmOrderList = listCreate(mtmCopyOrder,mtmFreeOrder);
    OUTPUT_FILE = output_file;
    mtmFacultyList = listCreate(mtmCopyFaculty,mtmFreeFaculty);
    Faculty faculty;
    for(int i = 0;i < UNKNOWN;i++){
        faculty = malloc(sizeof(*faculty));
        faculty->total_income = 0;
        faculty->id = (TechnionFaculty) i;
        listInsertFirst(mtmFacultyList,faculty);
    }
}

void mtmDestroyEscapeTechnion(){
    setDestroy(mtmCompanySet);
    setDestroy(mtmRoomSet);
    setDestroy(mtmEscaperSet);
    listDestroy(mtmOrderList);
    listDestroy(mtmFacultyList);
}

//-----------------------------------------------------------------------------
List mtmSetToList(Set set,CopyListElement copy,FreeListElement free){
    if(!set)
        return NULL;
    List list = listCreate(copy, free);
    int first = 0;
    listInsertFirst(list,setGetFirst(set));

    SET_FOREACH(SetElement,set_element,set){
        if (first == 0)
            first = 1;
        else{
            listGetFirst(list);
            listInsertAfterCurrent(list,set_element);
        }
    }

    return list;
}

int mtmCompareRoomsForRecommandedOrder(ListElement room1_in,
                                       ListElement room2_in){
    Room room1 = room1_in,room2 = room2_in;
    Escaper escaper = ESCAPER_FOR_RECOMANDED_ORDERING;
    int room1_metric = ((room1->num_ppl - NUM_OF_ORDERING_PEOPLE)*
                        (room1->num_ppl - NUM_OF_ORDERING_PEOPLE))+
                       ((room1->difficulty - escaper->skill_level)*
                       (room1->difficulty - escaper->skill_level));
    int room2_metric = ((room2->num_ppl - NUM_OF_ORDERING_PEOPLE)*
                        (room2->num_ppl - NUM_OF_ORDERING_PEOPLE))+
                       ((room2->difficulty - escaper->skill_level)*
                        (room2->difficulty - escaper->skill_level));

    if(room1_metric-room2_metric != 0)
        return room1_metric-room2_metric;
    else if(abs(room1->faculty-escaper->faculty)-
            abs(room2->faculty-escaper->faculty) != 0)
        return abs(room1->faculty-escaper->faculty)-
               abs(room2->faculty-escaper->faculty);
    else
        return room1->faculty - room2->faculty;

}
//-----------------------------------------------------------------------------

MtmErrorCode mtmCompanyAdd (char *email, TechnionFaculty faculty)
{
    if(!email)
        return MTM_NULL_PARAMETER;
    if(!strstr(email,"@") || faculty < 0 || faculty >= UNKNOWN)
        return MTM_INVALID_PARAMETER;

    Company company = malloc(sizeof(*company));
    if(!company)
        return MTM_OUT_OF_MEMORY;

    company->email = malloc(sizeof(char)*(strlen(email)+1));
    if(!(company->email)){
        free(company);
        return MTM_OUT_OF_MEMORY;
    }
    strcpy(company->email,email);
    company->faculty = faculty;

    if(setIsIn(mtmCompanySet,company)){
        mtmFreeCompany(company);
        return MTM_EMAIL_ALREADY_EXISTS;
    }

    SET_FOREACH(Escaper,escaper,mtmEscaperSet){
        if(!strcmp(email,escaper->email)){
            mtmFreeCompany(company);
            return MTM_EMAIL_ALREADY_EXISTS;
        }
    }

    assert(setAdd(mtmCompanySet,company)==SET_SUCCESS);

    return MTM_SUCCESS;
}

MtmErrorCode mtmCompanyRemove(char *email)
{
    if(!email)
        return MTM_NULL_PARAMETER;
    if(!strstr(email,"@"))
        return MTM_INVALID_PARAMETER;

    SET_FOREACH(Company,company,mtmCompanySet){
        if(!strcmp(email,company->email)) {
            LIST_FOREACH(Order,order,mtmOrderList){
                SET_FOREACH(Room,room,mtmRoomSet) {
                    if(order->faculty == room->faculty &&
                       order->room_id == room->id &&
                       !strcmp(email,room->email))
                        return MTM_RESERVATION_EXISTS;
                }
            }//Check Reservations
            Room room;
            int end = 0;

            while(end != 1){
                room = setGetFirst(mtmRoomSet);
                while(room != NULL){
                    if(!strcmp(room->email,email)) {
                        setRemove(mtmRoomSet, room);
                        break;
                    }
                    room = setGetNext(mtmRoomSet);
                    if(room == NULL)
                        end = 1;
                }
            }

            setRemove(mtmCompanySet, company);
            return MTM_SUCCESS;
        }
    }
    return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
}

MtmErrorCode mtmRoomAdd (char *email, int id,int price, int num_ppl,
                         int start_hour, int stop_hour, int difficulty)
{
    if(!email)
        return MTM_NULL_PARAMETER;
    if(!strstr(email,"@")|| id < 1 || price < 4 || price % 4 || num_ppl < 1 ||
       stop_hour - start_hour < 1 || start_hour<0 || start_hour > 23 ||
       stop_hour < 1 || stop_hour > 24 || difficulty < 1 ||
       difficulty > 10)
        return MTM_INVALID_PARAMETER;
    Company company = NULL;

    SET_FOREACH(Company,company_in,mtmCompanySet){
        if(!strcmp(company_in->email,email))
            company = company_in;
    }

    if(!company)
        return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;

    SET_FOREACH(Room,room,mtmRoomSet){
        if(room->faculty == company->faculty && room->id == id)
            return MTM_ID_ALREADY_EXIST;
    }

    Room room = malloc(sizeof(*room));
    if(!room)
        return MTM_OUT_OF_MEMORY;

    room->email = malloc(sizeof(char)*(strlen(email)+1));
    if(!(room->email))
        return MTM_OUT_OF_MEMORY;

    strcpy(room->email,email);
    room->faculty = company->faculty;
    room->id = id;
    room->price = price;
    room->num_ppl = num_ppl;
    room->start_hour = start_hour;
    room->stop_hour = stop_hour;
    room->difficulty = difficulty;

    assert(setAdd(mtmRoomSet,room)==SET_SUCCESS);
    return MTM_SUCCESS;
}

MtmErrorCode mtmRoomRemove (TechnionFaculty faculty, int id)
{
    if(faculty<0 || faculty >= UNKNOWN || id < 1)
        return MTM_INVALID_PARAMETER;
    Room room = NULL;

    SET_FOREACH(Room,room_in,mtmRoomSet){
        if(room_in->faculty == faculty && room_in->id == id)
            room = room_in;
    }

    if(!room)
        return MTM_ID_DOES_NOT_EXIST;

    LIST_FOREACH(Order,order,mtmOrderList){
        if(order->faculty == faculty && order->room_id == id){
            return MTM_RESERVATION_EXISTS;
        }
    }

    assert(setRemove(mtmRoomSet,room)==SET_SUCCESS);
    return MTM_SUCCESS;
}

MtmErrorCode mtmEscaperAdd (char* email,TechnionFaculty faculty,
                            int skill_level)
{
    if(!email)
        return MTM_NULL_PARAMETER;
    if(!strstr(email,"@") || faculty < 0 || faculty >= UNKNOWN ||
       skill_level < 1 || skill_level > 10)
        return MTM_INVALID_PARAMETER;

    Escaper escaper = malloc(sizeof(*escaper));
    if(!escaper)
        return MTM_OUT_OF_MEMORY;

    escaper->email = malloc(sizeof(char)*(strlen(email)+1));
    if(!(escaper->email)){
        free(escaper);
        return MTM_OUT_OF_MEMORY;
    }
    strcpy(escaper->email,email);

    escaper->faculty = faculty;
    escaper->skill_level = skill_level;

    if(setIsIn(mtmEscaperSet,escaper)){
        mtmFreeEscaper(escaper);
        return MTM_EMAIL_ALREADY_EXISTS;
    }

    SET_FOREACH(Company,company,mtmCompanySet){
        if(!strcmp(company->email,email)){
            mtmFreeEscaper(escaper);
            return MTM_EMAIL_ALREADY_EXISTS;
        }
    }

    assert(setAdd(mtmEscaperSet,escaper)==SET_SUCCESS);

    return MTM_SUCCESS;
}

MtmErrorCode mtmEscaperRemove (char *email)
{
    if(!email)
        return MTM_NULL_PARAMETER;
    if(!strstr(email,"@"))
        return MTM_INVALID_PARAMETER;
    Escaper escaper = NULL;

    SET_FOREACH(Escaper,escaper_in,mtmEscaperSet){
        if(!strcmp(escaper_in->email,email))
            escaper = escaper_in;
    }

    if(!escaper)
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;

    Order order;
    int end = 0;

    while(end != 1){
        order = listGetFirst(mtmOrderList);
        while(order != NULL){
            if(!strcmp(order->escaper->email,email)) {
                listRemoveCurrent(mtmOrderList);
                break;
            }
            order = listGetNext(mtmOrderList);
            if(order == NULL)
                end = 1;
        }
    }

    assert(setRemove(mtmEscaperSet,escaper)==SET_SUCCESS);
    return MTM_SUCCESS;
}
MtmErrorCode mtmEscaperOrder (char *email, TechnionFaculty faculty,int room_id,
                              int days_to_order, int hour, int num_ppl)
{
    if(!email)
        return MTM_NULL_PARAMETER;
    if(!strstr(email,"@") || faculty < 0 || faculty >= UNKNOWN || room_id < 1
       || num_ppl < 1 || hour < 0 || hour > 23 || days_to_order < 0) {
        return MTM_INVALID_PARAMETER;
    }
    Escaper escaper = NULL;
    Room room = NULL;
    SET_FOREACH(Escaper,escaper_in,mtmEscaperSet){
        if(!strcmp(escaper_in->email,email))
            escaper = escaper_in;
    }

    if(escaper==NULL){
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    }

    SET_FOREACH(Room,room_in,mtmRoomSet){
        if(room_in->faculty == faculty && room_in->id == room_id)
            room = room_in;
    }

    if(room==NULL){
        return MTM_ID_DOES_NOT_EXIST;
    }

    LIST_FOREACH(Order,order,mtmOrderList){
        if((!strcmp(escaper->email,order->escaper->email)) &&
           order->days_to_order == days_to_order && order->hour == hour)
            return MTM_CLIENT_IN_ROOM;
    }
    if(hour < room->start_hour || hour >= room->stop_hour)
        return MTM_ROOM_NOT_AVAILABLE;
    LIST_FOREACH(Order,order,mtmOrderList){
        if(order->faculty==faculty && order->room_id == room_id &&
           order->days_to_order == days_to_order && order->hour == hour)
            return MTM_ROOM_NOT_AVAILABLE;
    }
    Order order=malloc(sizeof(*order));
    order->escaper=escaper;
    order->faculty=faculty;
    order->days_to_order=days_to_order;
    order->hour=hour;
    order->num_of_people=num_ppl;
    order->room_id=room_id;
    listInsertLast(mtmOrderList, order);
    return MTM_SUCCESS;
}

MtmErrorCode mtmEscaperRecommend (char *email,int num_ppl)
{
    if(!email)
        return MTM_NULL_PARAMETER;
    if(!strstr(email,"@") || num_ppl < 1)
        return MTM_INVALID_PARAMETER;
    Escaper escaper = NULL;
    SET_FOREACH(Escaper,escaper_in,mtmEscaperSet){
        if(!strcmp(escaper_in->email,email))
            escaper = escaper_in;
    }
    if(!escaper)
        return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
    ESCAPER_FOR_RECOMANDED_ORDERING = escaper;
    NUM_OF_ORDERING_PEOPLE = num_ppl;
    if(setGetSize(mtmRoomSet) == 0)
        return MTM_NO_ROOMS_AVAILABLE;
    List mtmRoomList = mtmSetToList(mtmRoomSet,mtmCopyRoom,mtmFreeRoom);
    listSort(mtmRoomList,mtmCompareRoomsForRecommandedOrder);

    Room room = listGetFirst(mtmRoomList);

    int time_taken = 0;
    for(int day = 0; day < listGetSize(mtmOrderList)+10; day++){
        for(int hour = room->start_hour; hour<room->stop_hour;hour++){
            LIST_FOREACH(Order,order,mtmOrderList){
                if(order->days_to_order==day && order->hour == hour&&
                   order->faculty == room->faculty &&
                   order->room_id == room->id)
                    time_taken = 1;
            }
            if(time_taken==0){
                mtmEscaperOrder(email,room->faculty,room->id,day,hour,num_ppl);
                break;
            }
        }
        if(time_taken==0)
            break;
        else
            time_taken = 0;
    }
    listDestroy(mtmRoomList);
    return MTM_SUCCESS;
}

MtmErrorCode mtmReportDay()
{
    Room room = NULL;
    int total_price = 0;
    int total_orders = 0;
    LIST_FOREACH(Order,order,mtmOrderList){
        if(order->days_to_order==0)
            total_orders++;
    }
    listSort(mtmOrderList,mtmCompareOrder);

    mtmPrintDayHeader(OUTPUT_FILE,DAY_NUMBER,total_orders);

    Order order;
    int end = 0;
    order = listGetFirst(mtmOrderList);

    while(end != 1 && order){
        while(order != NULL){
            if(order->days_to_order == 0) {
                SET_FOREACH(Room,room_in,mtmRoomSet){
                    if(room_in->faculty == order->faculty &&
                       room_in->id == order->room_id)
                        room = room_in;}
                assert(room != NULL);
                if(order->escaper->faculty == room->faculty)
                    total_price = ((room->price)*(order->num_of_people)*3)/4;
                else
                    total_price = (room->price)*(order->num_of_people);
                LIST_FOREACH(Faculty,faculty,mtmFacultyList) {
                    if(faculty->id == order->faculty)
                        faculty->total_income += total_price;
                }
                mtmPrintOrder(OUTPUT_FILE,order->escaper->email,
                              order->escaper->skill_level,order->escaper->faculty,
                              room->email,room->faculty,order->room_id,order->hour,
                              room->difficulty,order->num_of_people,total_price);
                listRemoveCurrent(mtmOrderList);
                break;
            }
            else{
                order = setGetNext(mtmRoomSet);
                if(order == NULL)
                    end = 1;
            }
        }
        order = listGetFirst(mtmOrderList);
    }

    LIST_FOREACH(Order,order_in,mtmOrderList){
        order_in->days_to_order--;
    }

    mtmPrintDayFooter(OUTPUT_FILE,DAY_NUMBER);
    DAY_NUMBER++;

    return MTM_SUCCESS;
}

MtmErrorCode mtmReportBest()
{
    listSort(mtmFacultyList,mtmCompareFaculty);
    int total_income = 0;
    Faculty faculty = NULL;
    LIST_FOREACH(Faculty,faculty_in,mtmFacultyList){
        total_income +=faculty_in->total_income;
    }
    mtmPrintFacultiesHeader(OUTPUT_FILE,UNKNOWN,DAY_NUMBER,total_income);
    faculty = listGetFirst(mtmFacultyList);
    mtmPrintFaculty(OUTPUT_FILE,faculty->id,faculty->total_income);
    faculty = listGetNext(mtmFacultyList);
    mtmPrintFaculty(OUTPUT_FILE,faculty->id,faculty->total_income);
    faculty = listGetNext(mtmFacultyList);
    mtmPrintFaculty(OUTPUT_FILE,faculty->id,faculty->total_income);
    mtmPrintFacultiesFooter(OUTPUT_FILE);
    return MTM_SUCCESS;
}

/*-----------------------------------------------------------------------------
 * ----------------------------------------------------------------------------
 * ----------------------------------------------------------------------------
 *                               PRINTS
 */

void printCompany(Company company)
{
    fprintf(OUTPUT_FILE,"email: %s faculty: %d\n",company->email, company->faculty);
    return;
}

void printRoom(Room room)
{
    fprintf(OUTPUT_FILE,"faculty: %d id: %d email: %s price: %d num_ppl: %d "
                    "start_hour: %d stop_hour: %d difficulty: %d\n",
            room->faculty,
            room->id, room->email, room->price, room->num_ppl,
            room->start_hour, room->stop_hour, room->difficulty);
    return;
}

void printEscaper(Escaper escaper)
{
    fprintf(OUTPUT_FILE, "email: %s faculty: %d skill_level: %d\n", escaper->email,
            escaper->faculty,
            escaper->skill_level);
    return;
}

void printOrder(Order order)
{
    fprintf(OUTPUT_FILE, "faculty: %d room_id: %d days_to_order: %d hour: %d"
                    " num_of_people: %d\n",
            order->faculty, order->room_id,
            order->days_to_order, order->hour, order->num_of_people);
    printEscaper(order->escaper);
    return;
}

void printCompanySet()
{
    int i=0;
    SET_FOREACH(Company, company, mtmCompanySet) {
        fprintf(OUTPUT_FILE,"company %d: ", i);
        i++;
        printCompany(company);
    }
    return;
}
void printRoomSet()
{
    int i=0;
    SET_FOREACH(Room, room, mtmRoomSet) {
        fprintf(OUTPUT_FILE,"room %d: ", i);
        i++;
        printRoom(room);
    }
    return;
}
void printEscaperSet()
{
    int i=0;
    SET_FOREACH(Escaper, escaper, mtmEscaperSet) {
        fprintf(OUTPUT_FILE,"escaper %d: ", i);
        i++;
        printEscaper(escaper);
    }
    return;
}
void printOrderList()
{
    int i=0;
    LIST_FOREACH(Order, order, mtmOrderList) {
        fprintf(OUTPUT_FILE,"order %d: ", i);
        i++;
        printOrder(order);
    }
    return;
}