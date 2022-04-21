#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libtasn1.h"

unsigned char data[256];
int data_size = sizeof(data);

int main(int argc, char *argv[])
{
    asn1_retCode result;
    ASN1_TYPE definitions = ASN1_TYPE_EMPTY;
    ASN1_TYPE asn1_element = ASN1_TYPE_EMPTY;
    char errorDescription[ASN1_MAX_ERROR_DESCRIPTION_SIZE];
    const char *treefile = "pkix.asn";

    printf("\n\n/****************************************/\n");
    printf("/*     Test sequence : coding-decoding  */\n");
    printf("/****************************************/\n\n");

    result = asn1_parser2tree(treefile, &definitions, errorDescription);

    if (result != ASN1_SUCCESS)
    {
        asn1_perror(result);
        printf("ErrorDescription = %s\n\n", errorDescription);
        exit(1);
    }

    result = asn1_create_element(definitions, "MYPKIX1.Dss-Sig-Value", &asn1_element);
    if (result != ASN1_SUCCESS)
    {
        fprintf(stderr, "asn1_create_element(): ");
        asn1_perror(result);
        exit(1);
    }

    result = asn1_write_value(asn1_element, "r", "26", 1);
    if (result != ASN1_SUCCESS)
    {
        fprintf(stderr, "asn1_write_value(): r ");
        asn1_perror(result);
        exit(1);
    }
    result = asn1_write_value(asn1_element, "s", "23", 1);
    if (result != ASN1_SUCCESS)
    {
        fprintf(stderr, "asn1_write_value(): s ");
        asn1_perror(result);
        exit(1);
    }
    result = asn1_write_value(asn1_element, "other.x", "16", 1);
    if (result != ASN1_SUCCESS)
    {
        fprintf(stderr, "asn1_write_value(): other.x ");
        asn1_perror(result);
        exit(1);
    }
    result = asn1_write_value(asn1_element, "other.y.y1", "17", 1);
    if (result != ASN1_SUCCESS)
    {
        fprintf(stderr, "asn1_write_value(): other.y.y1 ");
        asn1_perror(result);
        exit(1);
    }

    result = asn1_write_value(asn1_element, "z", "", 1);
    if (result != ASN1_SUCCESS)
    {
        fprintf(stderr, "asn1_write_value(): z");
        asn1_perror(result);
        exit(1);
    }

    FILE *output= stdout;
    if (output == NULL)
    {
        fprintf(stderr, "open() ");
    }
    asn1_print_structure(output, asn1_element, "MYPKIX1.Dss-Sig-Value.r", ASN1_PRINT_ALL );

    /* Clear the definition structures */
    asn1_delete_structure(&definitions);
}
