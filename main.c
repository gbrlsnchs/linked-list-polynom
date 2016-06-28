#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct polynom {
    float coef;
    int exp;
    struct polynom *next;
} polynom;

void printPolynom(polynom *head);
void push(polynom **head, float coef, int exp);
polynom *pop(polynom **head);
void purge(polynom **head);
void writeInFile(polynom *node, FILE *file);
polynom *getPolynom(polynom **head);
polynom *getSum(polynom *nodeOne, polynom *nodeTwo);
polynom *getSub(polynom *nodeOne, polynom *nodeTwo);
polynom *getMult(polynom *nodeOne, polynom *nodeTwo);
polynom *getDiv(polynom *nodeOne, polynom *nodeTwo);
float getRoot(polynom *node);
polynom *getSorted(polynom *node);
float getPolynomValue(polynom *node, float x);

int main(int argc, char **argv) {
    // resets the output file
    fclose(fopen("saida.txt", "w"));

    int opAmount = 0;
    int polAmount = 0;
    int polExp = 0;
    float polCoef = 0.f;
    float x = 0.f;
    char opType = '\0';

    FILE *input;
    FILE *output;

    input = fopen("entrada.txt", "r");
    output = fopen("saida.txt", "a");

    struct polynom *head = NULL;

    fscanf(input, "%d", &opAmount);

    for (int i = 0; i < opAmount; i++) {
        fscanf(input, " %c", &opType);

        if (i != 0) {
            fprintf(output, "\n");
        }

        if (opType == 'V') {
            fscanf(input, "%d", &polAmount);

            for (int i = 0; i < polAmount; i++) {
                fscanf(input, "%g", &polCoef);
                fscanf(input, "%d", &polExp);
                push(&head, polCoef, polExp);
            }

            polynom *pol = getPolynom(&head);

            fprintf(output, "P(x) = ");
            writeInFile(pol, output);

            fscanf(input, "%g", &x);

            fprintf(output, "\nP(%g) = %g", x, getPolynomValue(pol, x));
            purge(&pol);

            fprintf(output, "\n");
        } else if (opType == '+') {
            fscanf(input, "%d", &polAmount);

            for (int i = 0; i < polAmount; i++) {
                fscanf(input, "%g", &polCoef);
                fscanf(input, "%d", &polExp);

                push(&head, polCoef, polExp);
            }

            polynom *polOne = getPolynom(&head);

            fscanf(input, "%d", &polAmount);

            for (int i = 0; i < polAmount; i++) {
                fscanf(input, "%g", &polCoef);
                fscanf(input, "%d", &polExp);

                push(&head, polCoef, polExp);
            }

            polynom *polTwo = getPolynom(&head);

            fprintf(output, "P1(x) = ");
            writeInFile(polOne, output);
            fprintf(output, "\n");
            fprintf(output, "P2(x) = ");
            writeInFile(polTwo, output);
            fprintf(output, "\n");
            fprintf(output, "Psoma(x) = ");
            writeInFile(getSum(polOne, polTwo), output);

            purge(&polOne);
            purge(&polTwo);

            fprintf(output, "\n");
        } else if (opType == '-') {
            fscanf(input, "%d", &polAmount);

            for (int i = 0; i < polAmount; i++) {
                fscanf(input, "%g", &polCoef);
                fscanf(input, "%d", &polExp);

                push(&head, polCoef, polExp);
            }

            polynom *polOne = getPolynom(&head);

            fscanf(input, "%d", &polAmount);

            for (int i = 0; i < polAmount; i++) {
                fscanf(input, "%g", &polCoef);
                fscanf(input, "%d", &polExp);

                push(&head, polCoef, polExp);
            }

            polynom *polTwo = getPolynom(&head);

            fprintf(output, "P1(x) = ");
            writeInFile(polOne, output);
            fprintf(output, "\n");
            fprintf(output, "P2(x) = ");
            writeInFile(polTwo, output);
            fprintf(output, "\n");
            fprintf(output, "Psubtração(x) = ");
            writeInFile(getSub(polOne, polTwo), output);

            purge(&polOne);
            purge(&polTwo);

            fprintf(output, "\n");
        } else if (opType == '*') {
            fscanf(input, "%d", &polAmount);

            for (int i = 0; i < polAmount; i++) {
                fscanf(input, "%g", &polCoef);
                fscanf(input, "%d", &polExp);

                push(&head, polCoef, polExp);
            }

            polynom *polOne = getPolynom(&head);

            fscanf(input, "%d", &polAmount);

            for (int i = 0; i < polAmount; i++) {
                fscanf(input, "%g", &polCoef);
                fscanf(input, "%d", &polExp);

                push(&head, polCoef, polExp);
            }

            polynom *polTwo = getPolynom(&head);

            fprintf(output, "P1(x) = ");
            writeInFile(polOne, output);
            fprintf(output, "\n");
            fprintf(output, "P2(x) = ");
            writeInFile(polTwo, output);
            fprintf(output, "\n");
            fprintf(output, "Pmultiplicação(x) = ");

            writeInFile(getMult(polOne, polTwo), output);
            purge(&polOne);
            purge(&polTwo);

            fprintf(output, "\n");
        } else if (opType == '/') {
            fscanf(input, "%d", &polAmount);

            for (int i = 0; i < polAmount; i++) {
                fscanf(input, "%g", &polCoef);
                fscanf(input, "%d", &polExp);

                push(&head, polCoef, polExp);
            }

            polynom *polOne = getPolynom(&head);

            fscanf(input, "%d", &polAmount);

            for (int i = 0; i < polAmount; i++) {
                fscanf(input, "%g", &polCoef);
                fscanf(input, "%d", &polExp);

                push(&head, polCoef, polExp);
            }

            polynom *polTwo = getPolynom(&head);

            fprintf(output, "Q(x) = ");
            writeInFile(polOne, output);
            fprintf(output, "\n");
            fprintf(output, "P(x) = ");
            writeInFile(polTwo, output);
            fprintf(output, "\n");
            fprintf(output, "Pdivisão(x) = ");
            writeInFile(getDiv(polOne, polTwo), output);

            purge(&polOne);
            purge(&polTwo);

            fprintf(output, "\n");
        }
    }

    fclose(input);
    fclose(output);
}

void printPolynom(polynom *head) {
    if (head) {
        while (head) {
            head = head->next;
        }
    }
}

void push(polynom **head, float coef, int exp) {
    if (coef != 0) {
        polynom *newHead = (polynom *)malloc(sizeof(polynom));
        newHead->coef = coef;
        newHead->exp = exp;
        newHead->next = *head;
        *head = newHead;
    }
}

polynom *pop(polynom **head) {
    if (!*head) {
        return NULL;
    }

    polynom *deleted = NULL;
    deleted = (polynom *)malloc(sizeof(polynom));

    deleted->coef = (*head)->coef;
    deleted->exp = (*head)->exp;
    deleted->next = (*head)->next;
    *head = (*head)->next;

    return deleted;
}

void purge(polynom **head) {
    while (*head) {
        pop(head);
    }

    free(*head);
}

void writeInFile(polynom *node, FILE *file) {
    if (node) {
        writeInFile(node->next, file);

        // prints plus sign if not the first coef in expression and if positive
        if (node->next) {
            if (node->coef > 0) {
                fprintf(file, " + ");
            }
        }

        // prints a minus sign if coef is negative, regardless if it's first coef
        if (node->coef < 0) {
            fprintf(file, " - ");
        }

        //
        if (node->coef != 0 && node->coef != 1 || node->coef == 1 && node->exp == 0) {
            fprintf(file, "%g", fabs(node->coef));

            if (node->exp != 0 && node->coef != 1) {
                fprintf(file, " ");
            }
        }

        if (node->coef != 0) {
            if (node->exp != 0 && node->exp != 1) {
                fprintf(file, "x^%d", node->exp);
            } else if (node->exp == 1) {
                fprintf(file, "x");
            }
        }
    }
}

polynom *getPolynom(polynom **head) {
    if (!*head) {
        return NULL;
    }

    polynom *value = NULL;
    value = (polynom *)malloc(sizeof(polynom));

    value->coef = (*head)->coef;
    value->exp = (*head)->exp;
    value->next = getPolynom(&(*head)->next);
    pop(head);

    return value;
}

polynom *getSum(polynom *nodeOne, polynom *nodeTwo) {
    if (!nodeOne && !nodeTwo) {
        return NULL;
    }

    if (nodeOne && nodeTwo) {
        polynom *value = NULL;
        value = (polynom *)malloc(sizeof(polynom));

        if (nodeOne->exp > nodeTwo->exp) {
            value->coef = nodeOne->coef;
            value->exp = nodeOne->exp;
            value->next = getSum(nodeOne->next, nodeTwo);
        } else if (nodeOne->exp < nodeTwo->exp) {
            value->coef = nodeTwo->coef;
            value->exp = nodeTwo->exp;
            value->next = getSum(nodeOne, nodeTwo->next);
        } else {
            value->coef = nodeOne->coef + nodeTwo->coef;
            value->exp = nodeOne->exp;
            value->next = getSum(nodeOne->next, nodeTwo->next);
        }

        return value;
    }

    if (nodeOne) {
        return nodeOne;
    }

    if (nodeTwo) {
        return nodeTwo;
    }
}

polynom *getSub(polynom *nodeOne, polynom *nodeTwo) {
    if (!nodeOne && !nodeTwo) {
        return NULL;
    }

    if (nodeOne && nodeTwo) {
        polynom *value = NULL;
        value = (polynom *)malloc(sizeof(polynom));

        if (nodeOne->exp > nodeTwo->exp) {
            value->coef = nodeOne->coef;
            value->exp = nodeOne->exp;
            value->next = getSub(nodeOne->next, nodeTwo);
        } else if (nodeOne->exp < nodeTwo->exp) {
            value->coef = nodeTwo->coef;
            value->exp = nodeTwo->exp;
            value->next = getSub(nodeOne, nodeTwo->next);
        } else {
            value->coef = nodeOne->coef - nodeTwo->coef;
            value->exp = nodeOne->exp;
            value->next = getSub(nodeOne->next, nodeTwo->next);
        }

        return value;
    }

    if (nodeOne) {
        return nodeOne;
    }

    if (nodeTwo) {
        return nodeTwo;
    }
}

polynom *getMult(polynom *nodeOne, polynom *nodeTwo) {
    if (!nodeOne || !nodeTwo) {
        return NULL;
    }

    polynom *value = NULL;
    value = (polynom *)malloc(sizeof(polynom));

    if (!nodeOne->next) {
        value->coef = nodeOne->coef * nodeTwo->coef;
        value->exp = nodeOne->exp + nodeTwo->exp;
        value->next = getMult(nodeOne, nodeTwo->next);
    } else {
        value->coef = nodeOne->coef * nodeTwo->coef;
        value->exp = nodeOne->exp + nodeTwo->exp;
        value->next = NULL;
        value->next = (polynom *)malloc(sizeof(polynom));
        value->next->coef = nodeOne->coef * nodeTwo->next->coef;
        value->next->exp = nodeOne->exp + nodeTwo->next->exp;
        value->next->next = getMult(nodeOne->next, nodeTwo);
    }

    return getSorted(value);
}

polynom *getDiv(polynom *nodeOne, polynom *nodeTwo) {
    if (!nodeOne || !nodeTwo || !nodeTwo->next) {
        return NULL;
    }

    float root = getRoot(nodeOne);

    polynom *value = NULL;
    value = (polynom *)malloc(sizeof(polynom));

    value->coef = nodeTwo->coef;

    value->exp = nodeTwo->exp - 1;
    nodeTwo->next->coef = root * value->coef + nodeTwo->next->coef;
    value->next = getDiv(nodeOne, nodeTwo->next);

    return value;
}

float getRoot(polynom *node) {
    return node->next ? node->next->coef * -1.f : 0.f;
}

polynom *getSorted(polynom *node) {
    if (!node) {
        return NULL;
    }

    polynom *value = NULL;
    value = (polynom *)malloc(sizeof(polynom));

    value->coef = node->coef;
    value->exp = node->exp;

    if (node->next) {
        if (node->exp < node->next->exp) {
            value->coef = node->next->coef;
            value->exp = node->next->exp;

            node->next->coef = node->coef;
            node->next->exp = node->exp;

            node->coef = value->coef;
            node->exp = value->exp;
        } else if (node->exp == node->next->exp) {
            value->coef = node->coef + node->next->coef;
            value->exp = node->exp;

            node->next = node->next->next;
        }
    }

    value->next = getSorted(node->next);

    return value;
}

float getPolynomValue(polynom *node, float x) {
    float result = 0.f;

    while (node) {
        result += node->coef * pow(x, node->exp);
        node = node->next;
    }

    return result;
}