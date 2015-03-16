#include <moonshine.h>
#include <cstdio>

int test1 ()
{
    printf ("Test #1:\tCorrect data\n");

    unsigned tares[] = {50, 5000, 10, 150};
    unsigned propors[] = {5, 500, 1, 15};
    unsigned res_volume = 5;
    unsigned increds[] = {10, 1350, 3, 40};
    unsigned correct_res = res_volume * 2;
    unsigned correct_remainder[] = {0, 350, 1, 10};
    unsigned result = 0;
    unsigned remainder [4];

    Moonshine msh (tares, 4);

    MOONSHINE_RETURN_CODE res;
    if ((res = msh.setProportions(propors, res_volume)) != MSH_OK)
    {
        printf ("Test #1:\tsetProportions() failed, return code %d\n", res);
        return -1;
    }

    msh.loadIngredients(increds);

    if ((res = msh.startDistillate()) != MSH_OK)
    {
        printf ("Test #1:\tstartDistillate() failed, return code %d\n", res);
        return -1;
    }

    if ((res = msh.getProduct(&result, remainder)) != MSH_OK)
    {
        printf ("Test #1:\tgetProduct() failed, return code %d\n", res);
        return -1;
    }

    if (result != correct_res)
    {
        printf ("Test #1:\tresult %u is wrong (right is %u)\n", result, correct_res);
        return -1;
    }

    for (size_t i = 0; i < 4; ++i)
    {
        if (remainder [i] != correct_remainder [i])
        {
            printf ("Test #1:\tremainder is wrong\n");
            return -1;
        }
    }

    printf ("Test #1:\tTest #1 passed\n");
    return 0;
}

int test2 ()
{
    printf ("Test #2:\t0-proportion\n");

    unsigned tares[] = {50, 678, 10, 150};

    unsigned propors[] = {5, 500, 1, 0};
    unsigned res_volume = 5;

    Moonshine msh (tares, 4);

    MOONSHINE_RETURN_CODE res;
    if ((res = msh.setProportions(propors, res_volume)) != MSH_WRONG_PROPORTIONS)
    {
        printf ("Test #2:\tsetProportions() wrong return code %d (we wait %d)\n", res, MSH_WRONG_PROPORTIONS);
        return -1;
    }

    printf ("Test #2:\tTest #2 passed\n");
    return 0;
}

int test3 ()
{
    printf ("Test #3:\tNot enough incredients & tares volume limit\n");

    unsigned tares[] = {50, 450, 10, 150};

    unsigned propors[] = {5, 500, 1, 15};
    unsigned res_volume = 5;

    unsigned increds[] = {10, 1350, 3, 40}; //we cant puts increds[i] > tares[i]

    Moonshine msh (tares, 4);

    MOONSHINE_RETURN_CODE res;

    if ((res = msh.setProportions(propors, res_volume)) != MSH_OK)
    {
        printf ("Test #3:\tsetProportions() failed, return code %d\n", res);
        return -1;
    }

    msh.loadIngredients(increds);

    if ((res = msh.startDistillate()) != MSH_NOT_ENOUGH_INCREDIENTS)
    {
        printf ("Test #3:\tstartDistillate() wrong return code %d (we wait %d)\n", res, MSH_NOT_ENOUGH_INCREDIENTS);
        return -1;
    }

    printf ("Test #3:\tTest #3 passed\n");
    return 0;
}

int test4 ()
{
    printf ("Test #4:\tWrong order function call\n");

    unsigned tares[] = {50, 5000, 10, 150};
    unsigned propors[] = {5, 500, 1, 15};
    unsigned res_volume = 5;
    unsigned increds[] = {10, 1350, 3, 40};

    unsigned result = 0;
    unsigned remainder [4];

    Moonshine msh (tares, 4);

    MOONSHINE_RETURN_CODE res;

    if ((res = msh.getProduct(&result, remainder)) != MSH_DONT_DISTILLATE)
    {
        printf ("Test #4:\tgetProduct() wrong error code %d (we wait for %d)\n", res, MSH_DONT_DISTILLATE);
        return -1;
    }

    if ((res = msh.startDistillate()) != MSH_NOT_PREPARED)
    {
        printf ("Test #4:\tstartDistillate() wrong error code %d (we wait for %d)\n", res, MSH_NOT_PREPARED);
        return -1;
    }

    if ((res = msh.setProportions(propors, res_volume)) != MSH_OK)
    {
        printf ("Test #4:\tsetProportions() failed, return code %d\n", res);
        return -1;
    }

    if ((res = msh.startDistillate()) != MSH_NOT_PREPARED)
    {
        printf ("Test #4:\tstartDistillate() (second call) wrong error code %d (we wait for %d)\n", res, MSH_NOT_PREPARED);
        return -1;
    }

    printf ("Test #4:\tTest #4 passed\n");
    return 0;
}

int test5 ()
{
    printf ("Test #5:\tCheck clearTares function\n");

    unsigned tares[] = {1600, 1600, 1600, 1600};
    unsigned propors[] = {50, 30, 70, 190};
    unsigned res_volume = 5;
    unsigned increds[] = {347, 1350, 689, 1150};
    unsigned correct_res = res_volume * 6;
    unsigned correct_remainder[] = {47, 1170, 269, 10};

    unsigned result = 0;
    unsigned remainder [4];

    Moonshine msh (tares, 4);

    MOONSHINE_RETURN_CODE res;
    if ((res = msh.setProportions(propors, res_volume)) != MSH_OK)
    {
        printf ("Test #5:\tsetProportions() failed, return code %d\n", res);
        return -1;
    }

    msh.loadIngredients(increds);
    msh.clearTares();

    if ((res = msh.startDistillate()) != MSH_NOT_PREPARED)
    {
        printf ("Test #5:\tstartDistillate() wrong error code %d (we wait for %d)\n", res, MSH_NOT_PREPARED);
        return -1;
    }

    msh.loadIngredients(increds);

    if ((res = msh.startDistillate()) != MSH_OK)
    {
        printf ("Test #5:\tstartDistillate() failed, return code %d\n", res);
        return -1;
    }

    if ((res = msh.getProduct(&result, remainder)) != MSH_OK)
    {
        printf ("Test #5:\tgetProduct() failed, return code %d\n", res);
        return -1;
    }

    if (result != correct_res)
    {
        printf ("Test #5:\tresult %u is wrong (right is %u)\n", result, correct_res);
        return -1;
    }

    for (size_t i = 0; i < 4; ++i)
    {
        if (remainder [i] != correct_remainder [i])
        {
            printf ("Test #5:\tremainder is wrong\n");
            return -1;
        }
    }

    printf ("Test #5:\tTest #5 passed\n");
    return 0;
}

int main ()
{
    printf ("==================== Welcome to libmoonshine test ====================\n");
    if (test1() != 0)
        printf ("Test #1:\tTest failed\n");

    printf ("\n");

    if (test2() != 0)
        printf ("Test #2:\tTest failed\n");

    printf ("\n");

    if (test3() != 0)
        printf ("Test #3:\tTest failed\n");

    printf ("\n");

    if (test4() != 0)
        printf ("Test #4:\tTest failed\n");

    printf ("\n");

    if (test5() != 0)
        printf ("Test #5:\tTest failed\n");

    printf ("\n");
    return 0;
}
