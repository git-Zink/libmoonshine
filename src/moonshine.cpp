#include "moonshine.h"

bool Moonshine::checkProportions()
{
    result_count = incredients[0] / proportions[0];
    //ищем минимальное количество порций, которое сможем сварить.
    for (size_t i = 0; i < incred_count; ++i)
    {
        result_count = std::min (result_count, incredients[i] / proportions[i]);
    }

    //если сварить ничего не можем, нехорошо
    return (result_count > 0);
}

Moonshine::Moonshine(const unsigned p_tares[], const size_t count)
{
    msh_prepared_status.increds_loaded = false;
    msh_prepared_status.propors_set = false;
    msh_prepared_status.msh_ready = false;

    incred_count = count;
    result_count = 0;
    result_volume = 0;

    tares_volumes.resize(incred_count);
    incredients.resize(incred_count);
    proportions.resize(incred_count);

    for (int i = 0; i < incred_count; ++i)
    {
        tares_volumes[i] = p_tares [i];
        incredients[i] = 0;
        proportions[i] = 0;
    }
}


Moonshine::~Moonshine()
{

}

MOONSHINE_RETURN_CODE Moonshine::setProportions(const unsigned p_propors[], const unsigned res_volume)
{
    for (int i = 0; i < incred_count; ++i)
    {
        if (p_propors[i] == 0) //во избежания деления на 0 в checkProportions()
            return MSH_WRONG_PROPORTIONS;

        proportions[i] = p_propors [i];
    }

    result_volume = res_volume;
    msh_prepared_status.propors_set = true;
    return MSH_OK;
}


void Moonshine::loadIngredients(unsigned p_incred[])
{
    for (size_t i = 0; i < incred_count; ++i)
        incredients[i] = std::min (p_incred[i], tares_volumes[i]);

    msh_prepared_status.increds_loaded = true;
}


MOONSHINE_RETURN_CODE Moonshine::startDistillate()
{
    if (!msh_prepared_status.increds_loaded || !msh_prepared_status.propors_set)
        return MSH_NOT_PREPARED;

    if (checkProportions())
    {
        result = result_count * result_volume;
        msh_prepared_status.msh_ready = true;

        return MSH_OK;
    }

    return MSH_NOT_ENOUGH_INCREDIENTS;
}

void Moonshine::clearTares()
{
    msh_prepared_status.increds_loaded = false;
    msh_prepared_status.msh_ready = false;

    result_count = 0;

    for (size_t i = 0; i < incred_count; ++i)
        incredients[i] = 0;
}


MOONSHINE_RETURN_CODE Moonshine::getProduct(unsigned *product, unsigned remainders[])
{
    if (msh_prepared_status.msh_ready)
    {
        *product = result;

        if (remainders != NULL)
        {
            for (size_t i = 0; i < incred_count; ++i)
                remainders[i] = incredients[i] - proportions[i] * result_count;
        }

        return MSH_OK;
    }

    return MSH_DONT_DISTILLATE;
}
