#define ARRAY_SIZE 10

int main()
{
    int array[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = i;
    }

    int sum = 0;

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        sum += array[i];
    }

    return 0;
}