/*
 * Класс-прототип самогонного аппарата.
 * Схема работы:
 * 1. В конструкторе задаются объемы тар для ингредиентов их количество
 * 2. Установить пропорции ингредиентов и количество спирта на выходе из одной порции
 * 3. Загрузить некоторое количество ингредиентов в тары (все что сверх объема - игнорируется)
 * 4. Запустить процесс дистилляции
 * 5. Получить результат. Необязателльный параметр - можно получить остаток ингредиентов
 */


#ifndef MOONSHINE_H
#define MOONSHINE_H

#include <algorithm>
#include <vector>

enum MOONSHINE_RETURN_CODE
{
    MSH_OK,
    MSH_WRONG_PROPORTIONS,
    MSH_NOT_PREPARED,
    MSH_NOT_ENOUGH_INCREDIENTS,
    MSH_DONT_DISTILLATE
};

class Moonshine
{
private:
    /*
     * отслежиаем состояние аппарата, для проверки правильной
     * последовательности функций (объявить - загрузить - дистиллировать)
     */
    struct
    {
        bool propors_set;
        bool increds_loaded;
        bool msh_ready;
    } msh_prepared_status;

    //количество ингридиентов
    size_t incred_count;

    /*
     * контейнеры для хранения
     *      - объема тары
     *      - нужных пропорций
     *      - доступных ингридиентов
     * соответственно
     */
    std::vector <unsigned> tares_volumes;
    std::vector <unsigned> proportions;
    std::vector <unsigned> incredients;


    /* результаты процесса */
    unsigned result; //итоговый объем спирта, который возвращается клиенту
    unsigned result_volume; //объем спирта с одной порции ингредиентов (согласно пропорциям)
    unsigned result_count; //количество порций (согласно пропорциям)

    bool checkProportions ();//хвататет ли ингредиентов и на сколько порций? так же устанавливается result_count

public:
    Moonshine (const unsigned p_tares[], const size_t count); //мастерим тары
    ~Moonshine ();

    MOONSHINE_RETURN_CODE setProportions(const unsigned p_propors[], const unsigned res_volume); //записываем рецепт

    void loadIngredients (unsigned p_incred[]); //готовим ингредиенты
    void clearTares(); //моем посуду, выкидываем излишки

    MOONSHINE_RETURN_CODE startDistillate (); //гоним!
    MOONSHINE_RETURN_CODE getProduct (unsigned *product, unsigned remainders[] = NULL); //получаем результат; по желанию - остаток ингредиентов
};

#endif //MOONSHINE_H
