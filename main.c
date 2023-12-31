#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mtm_ex3.h"
#include "EscapeTechnion.h"

MtmErrorCode openInputFile(int argc, char **argv, FILE ** file,
                           int *countChannels)
{
    for(int i = 1; i < argc - 1; i++)
    {
        if(strcmp(argv[i], "-i")==0){
            *file = fopen(argv[i+1],"r");
            if(!*file)
                return MTM_CANNOT_OPEN_FILE;
            else{
                (*countChannels)++;
                return MTM_SUCCESS;
            }
        }
    }
    *file = stdin;
    return MTM_SUCCESS;
}

MtmErrorCode openOutputFile(int argc, char **argv, FILE ** file,
                            int *countChannels)
{
    for(int i = 1; i < argc - 1; i++)
    {
        if(strcmp(argv[i], "-o")==0){
            *file = fopen(argv[i+1],"w");
            if(!*file)
                return MTM_CANNOT_OPEN_FILE;
            else{
                (*countChannels)++;
                return MTM_SUCCESS;
            }
        }
    }
    *file = stdout;
    return MTM_SUCCESS;
}

int main(int argc, char ** argv) {
    MtmErrorCode error;
    int count_channels = 0;
    FILE *inputFile;
    FILE *outputFile;

    if(argc !=1 && argc !=3 && argc !=5) {
        mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
        return 1;
    }

    error = openInputFile(argc, argv, &inputFile,&count_channels);
    if (error == MTM_CANNOT_OPEN_FILE) {
        mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
        return 1;
    }

    error = openOutputFile(argc, argv, &outputFile,&count_channels);
    if (error == MTM_CANNOT_OPEN_FILE) {
        mtmPrintErrorMessage(stderr, MTM_CANNOT_OPEN_FILE);
        return 1;
    }

    if(count_channels != (argc-1)/2) {
        mtmPrintErrorMessage(stderr,MTM_INVALID_COMMAND_LINE_PARAMETERS);
        return 1;
    }
    //End loading channels

    //And now Initialize Set and List objects
    mtmInitiateEscapeTechnion(outputFile);

    //Variables used in the reading of the file
    char line[MAX_LEN+1];
    char *chunk;
    int lineLength = MAX_LEN+1;
    //To make the code more readable;
    char *email;
    TechnionFaculty faculty;
    int id;
    int price;
    int num_ppl;
    char *working_hrs;
    int start_hour;
    int stop_hour;
    int difficulty;
    int skill_level;
    char *order_time;
    int day_to_order;
    int hour;

    //All heavy lifting is done here
    fgets(line,lineLength,inputFile);
    while((!feof(inputFile))){
        chunk = strtok(line," \t");

        if(!strcmp(chunk,"\n") || chunk[0] == '#'){
            error = MTM_SUCCESS;
        }
        else if     (!strcmp(chunk,"print")){
            chunk = strtok(NULL," \t\n");
            if(!strcmp(chunk,"company"))
                printCompanySet();
            else if(!strcmp(chunk,"room"))
                printRoomSet();
            else if(!strcmp(chunk,"escaper"))
                printEscaperSet();
            else if(!strcmp(chunk,"order"))
                printOrderList();
            else
                mtmPrintErrorMessage(stderr,MTM_INVALID_PARAMETER);
        }
        else if     (!strcmp(chunk,"company")) {
            chunk = strtok(NULL," \t\n");
            if     (!strcmp(chunk,"add")){
                email = strtok(NULL," \t\n");
                faculty = (TechnionFaculty)strtol(strtok(NULL," \t\n"),NULL,10);
                error = mtmCompanyAdd(email, faculty);
            }
            else if(!strcmp(chunk,"remove")){
                email = strtok(NULL," \t\n");
                error = mtmCompanyRemove(email);
            }
            else{
                mtmPrintErrorMessage(stderr,MTM_INVALID_PARAMETER);
            }
        }
        else if(!strcmp(chunk,"room")) {
            chunk = strtok(NULL," \t\n");
            if     (!strcmp(chunk,"add")){
                email = strtok(NULL," \t\n");
                id = strtol(strtok(NULL," \t\n"),NULL,10);
                price = strtol(strtok(NULL," \t\n"),NULL,10);
                num_ppl = strtol(strtok(NULL," \t\n"),NULL,10);
                working_hrs = strtok(NULL," \t\n");
                difficulty = strtol(strtok(NULL," \t\n"),NULL,10);
                start_hour = strtol(strtok(working_hrs,"- \t\n"),NULL,10);
                stop_hour = strtol(strtok(NULL,"- \t\n"),NULL,10);
                error = mtmRoomAdd(email,id,price,num_ppl,start_hour,
                                   stop_hour, difficulty);
            }
            else if(!strcmp(chunk,"remove")){
                faculty = (TechnionFaculty)strtol(strtok(NULL," \t\n"),NULL,10);
                id = strtol(strtok(NULL," \t\n"),NULL,10);
                error = mtmRoomRemove(faculty,id);
            }
            else{
                mtmPrintErrorMessage(stderr,MTM_INVALID_PARAMETER);
            }
        }
        else if(!strcmp(chunk,"escaper")) {
            chunk = strtok(NULL," \t\n");
            if     (!strcmp(chunk,"add")){
                email = strtok(NULL," \t\n");
                faculty = (TechnionFaculty)strtol(strtok(NULL," \t\n"),NULL,10);
                skill_level = strtol(strtok(NULL," \t\n"),NULL,10);
                error = mtmEscaperAdd(email,faculty,skill_level);
            }
            else if(!strcmp(chunk,"remove")) {
                email = strtok(NULL," \t\n");
                error = mtmEscaperRemove(email);
            }
            else if(!strcmp(chunk,"order")) {
                email = strtok(NULL," \t\n");
                faculty = (TechnionFaculty)strtol(strtok(NULL," \t\n"),NULL,10);
                id = strtol(strtok(NULL," \t\n"),NULL,10);
                order_time = strtok(NULL," \t\n");
                num_ppl = strtol(strtok(NULL," \t\n"),NULL,10);
                day_to_order = strtol(strtok(order_time,"- \t\n"),NULL,10);
                hour = strtol(strtok(NULL,"- \t\n"),NULL,10);
                error = mtmEscaperOrder(email,faculty,id,day_to_order,hour,
                                        num_ppl);
            }
            else if(!strcmp(chunk,"recommend")) {
                email = strtok(NULL," \t\n");
                num_ppl = strtol(strtok(NULL," \t\n"),NULL,10);
                error = mtmEscaperRecommend(email,num_ppl);
            }
            else{
                mtmPrintErrorMessage(stderr,MTM_INVALID_PARAMETER);
            }
        }
        else if(!strcmp(chunk,"report")) {
            chunk = strtok(NULL," \t\n");
            if     (!strcmp(chunk,"day")){
                error = mtmReportDay();
            }
            else if(!strcmp(chunk,"best")){
                error = mtmReportBest();
            }
            else{
                mtmPrintErrorMessage(stderr,MTM_INVALID_PARAMETER);
            }
        }
        else {
            mtmPrintErrorMessage(stderr,MTM_INVALID_PARAMETER);
        }
        if(error != MTM_SUCCESS)
            mtmPrintErrorMessage(stderr,error);

        fgets(line,lineLength,inputFile);
    }
    mtmDestroyEscapeTechnion();
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}