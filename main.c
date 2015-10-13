#include <stdio.h>
#include <stdlib.h>

float machConversion(float alt, float knots);

int main() {

    FILE *readIn = fopen("Alt_AS.dat", "rb"); //read the input file
    FILE *writeOut = fopen("CSV_OUTPUT.csv", "w"); //create a file to write to
    fprintf(writeOut, "Time,Altitude,Speed in Knots,Mach Number\n"); //write the header

    if (readIn == NULL) //check if the input file was properly read
    {
        printf("***ERROR reading file***");
    }

    int ch = getc(readIn);
    union
    {
        char bytes[4];
        float hold;
    } holder;

    float knots;
    float mach;
    float alt;
    int count = 0; //to calculate the time of the entry

    while (ch != EOF)
    {
        holder.bytes[3] = (char) ch;
        holder.bytes[2] = (char) getc(readIn);
        holder.bytes[1] = (char) getc(readIn);
        holder.bytes[0] = (char) getc(readIn);
        alt = holder.hold;

        holder.bytes[3] = (char) getc(readIn);
        holder.bytes[2] = (char) getc(readIn);
        holder.bytes[1] = (char) getc(readIn);
        holder.bytes[0] = (char) getc(readIn);
        knots = holder.hold;

        mach = machConversion(alt, knots);

        fprintf(writeOut, "%f,%f,%f,%f\n", count/10.0, alt, knots, mach);

        ch = getc(readIn);
        count++;
    }
    fclose(writeOut);
    fclose(readIn);
    return 0;
}

/**
 * Find the mach given the speed in knots at a certain altitude
 */
float machConversion(float alt, float knots)
{
    if (alt <= 10000)
        return knots / (661 - 23 * (alt / 10000));
    else if (alt <= 20000)
        return knots / (638 - 24 * ((alt - 10000) / 10000));
    else if (alt <= 30000)
        return knots / (614 - 25 * ((alt - 20000) / 10000));
    else if (alt <= 40000)
        return knots / (589 -  16 * ((alt - 30000) / 10000));
    else
        return knots / 573;
}