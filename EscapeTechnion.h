#ifndef ESCAPETECHNION_H_
#define ESCAPETECHNION_H_


#include <stdio.h>
#include <string.h>
#include "set.h"
#include "list.h"
#include <malloc.h>
#include "mtm_ex3.h"

typedef struct company_t
{
    char *email;
    TechnionFaculty faculty;
} *Company;

typedef struct room_t
{
    char *email;
    TechnionFaculty faculty;
    int id;
    int price;
    int num_ppl;
    int start_hour;
    int stop_hour;
    int difficulty;
} *Room;

typedef struct escaper_t
{
    char *email;
    TechnionFaculty faculty;
    int skill_level;
} *Escaper;

typedef struct order_t
{
    Escaper escaper;
    TechnionFaculty faculty;
    int room_id;
    int days_to_order;
    int hour;
    int num_of_people;
} *Order;

typedef struct faculty_t{
    TechnionFaculty id;
    int total_income;
}* Faculty;

static Set mtmCompanySet;
static Set mtmRoomSet;
static Set mtmEscaperSet;
static List mtmOrderList;
static int DAY_NUMBER;
static FILE *OUTPUT_FILE;

static Escaper ESCAPER_FOR_RECOMANDED_ORDERING;
static int NUM_OF_ORDERING_PEOPLE;

static SetElement mtmCopyCompany(SetElement company);
static void mtmFreeCompany(SetElement company);
static SetElement mtmCopyRoom(SetElement room);
static void mtmFreeRoom(SetElement room);
static int mtmCompareRoom(SetElement room1,SetElement room2);
static SetElement mtmCopyOrder(SetElement order);
static void mtmFreeOrder(SetElement order);
static int mtmCompareOrder(SetElement order1,SetElement order2);
static SetElement mtmCopyEscaper(SetElement escaper);
static void mtmFreeEscaper (SetElement escaper);
static int mtmCompareEscaper (SetElement escaper1,SetElement escaper2);
void mtmInitiateEscapeTechnion(FILE* output_file);
void mtmDestroyEscapeTechnion();
List mtmSetToList(Set set,CopyListElement copy,FreeListElement free);
int mtmCompareRoomsForRecommandedOrder(ListElement room1_in,
                                       ListElement room2_in);
MtmErrorCode mtmCompanyAdd (char *email, TechnionFaculty faculty);
MtmErrorCode mtmCompanyRemove(char *email);
MtmErrorCode mtmRoomAdd (char *email, int id,int price, int num_ppl,
                         int start_hour, int stop_hour, int difficulty);
MtmErrorCode mtmRoomRemove (TechnionFaculty faculty, int id);
MtmErrorCode mtmEscaperAdd (char* email,TechnionFaculty faculty,
                            int skill_level);
MtmErrorCode mtmEscaperRemove (char *email);
MtmErrorCode mtmEscaperOrder (char *email, TechnionFaculty faculty,int room_id,
                              int days_to_order, int hour, int num_ppl);
MtmErrorCode mtmEscaperRecommend (char *email,int num_ppl);
MtmErrorCode mtmReportDay();
MtmErrorCode mtmReportBest();

void printCompany(Company company);
void printRoom(Room room);
void printEscaper(Escaper escaper);
void printOrder(Order order);
void printCompanySet();
void printRoomSet();
void printEscaperSet();
void printOrderList();
#endif //ESCAPETECHNION_H_
