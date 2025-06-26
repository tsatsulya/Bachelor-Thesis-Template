/**
 * Проверяет допустимость преобразования между упакованными примитивными типами.
 * Основная идея: проверяет, можно ли безопасно преобразовать один упакованный тип
 * в другой, переисспользуя алгоритмы проверки преобразований для примитивных типов.
 */
bool IsLegalBoxedPrimitiveConversion(Type *target, Type *source) {
    Checker *checker = this->GetChecker()->AsChecker();

    // Проверка на null
    if (target == nullptr || source == nullptr) {
        return false;
    }

    // Обработка union-типов (особый случай)
    if (target->IsUnionType() && source->IsObjectType()) {
        // Получаем базовый примитивный тип для исходного типа
        Type *sourceUnboxed = checker->MaybeUnboxType(source);
        if (!sourceUnboxed || !sourceUnboxed->IsPrimitiveType()) {
            return false;
        }

        // Ищем упакованный тип в union, который можно распаковать
        Type *boxedUnionTarget = target->AsUnionType()->FindUnboxableType();
        if (!boxedUnionTarget) {
            return false;
        }

        // Проверяем совместимость базовых примитивных типов
        Type *targetUnboxed = checker->MaybeUnboxType(boxedUnionTarget);
        return targetUnboxed && targetUnboxed->IsPrimitiveType() &&
               this->IsAssignableTo(sourceUnboxed, target);
    }

    // Оба типа должны быть объектными
    if (!target->IsObjectType() || !source->IsObjectType()) {
        return false;
    }

    // Хотя бы один тип должен быть упакованным примитивом
    if (!target->AsObjectType()->IsBoxedPrimitive() &&
        !source->AsObjectType()->IsBoxedPrimitive()) {
        return false;
    }

    // Получаем базовые примитивные типы
    Type *targetUnboxed = checker->MaybeUnboxType(target);
    Type *sourceUnboxed = checker->MaybeUnboxType(source);

    // Особый случай для int-перечислений
    if (source->IsIntEnumType()) {
        targetUnboxed = checker->GlobalIntType();
    }

    // Проверяем что оба имеют примитивные базовые типы
    if (!targetUnboxed || !sourceUnboxed ||
        !targetUnboxed->IsPrimitiveType() ||
        !sourceUnboxed->IsPrimitiveType()) {
        return false;
    }

    // Проверяем совместимость примитивных типов
    return this->IsAssignableTo(sourceUnboxed, targetUnboxed);
}