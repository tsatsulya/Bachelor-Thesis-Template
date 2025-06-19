**Theory Part Structure: Eliminating Primitive Types**

**Introduction to the Theory Part**

**Chapter 1: Foundations of Programming Language Type Systems**
*   **1.1 What is a Type System?**
*   **1.2 Categories of Data Types**
    *   **1.2.1 Primitive Types:**
    *   **1.2.2 Reference Types (Objects):**
    *   **1.2.3 Value Types (where applicable - e.g., C# `struct`)**:
*  **1.3 Introduction to the Challenge:**
*  **1.4 The Traditional Approach (Illustrative Example, maybe Java first):**
*  **1.5 C#'s Approach: Explicit Value vs. Reference Types:**
*  **1.6 Kotlin's Approach: Abstracting the Primitive/Object Distinction:**
*  **1.7 The Role of Compiler Optimization (Tie it all together):**

**Chapter 2: High-Level Managed Programming Languages**
*   **2.1 Definition and Characteristics**
*   **2.2 The Runtime Environment**
*   **2.3 Automatic Memory Management (Garbage Collection)**

**Chapter 3: The Problem: Inconsistency with Primitive Types in Managed Languages**
*   **3.1 Lack of Uniformity in the Type System**
*   **3.2 Limitations in Object-Oriented Features**
*   **3.3 Performance and Overhead (if applicable)**
*   **3.4 Impact on Language Design and Features**

    **Chapter 4: Existing Approaches and Related Concepts**
*   **4.1 Languages with Uniform Object Models**
*   **4.2 Wrapper Classes / Boxing (Revisited)**
*   **4.3 Value Types vs. Reference Types (C#, .NET)**
*   **4.4 Research on Unified Type Systems**

**Chapter 5: Theoretical Foundations for Eliminating Primitives**
*   **5.1 Principles of a Fully Unified Type System**
*   **5.2 Designing Object Replacements for Primitives**
*   **5.3 Performance Considerations in a Unified Model**
*   **5.4 Impact on Memory Management**
*   **5.5 Implications for Language Semantics**
*   **5.6 Implications for the Type System**

**Conclusion to the Theory Part**

**References**





**Theory Part Structure: Eliminating Primitive Types**

**Introduction to the Theory Part**

Типовая система языка программирования служит фундаментом для формального определения его спецификации, обеспечивает статический анализ программ, поддержку оптимизаций кода и способствует улучшению его структурированности и читаемости.
Высокоуровневые языки программирования(Java, C#, Kotlin, ...) предоставляют разработчику мощные абстракции и безопасность кода посредством автоматического управления памятью и объектно-ориентированных парадигм. Многие из этих языков сохранили в себе исторически сложившееся разделение типов на "примитивные" типы и "объектные" или "ссылочные", призванное потенциально улучшить производительность в некоторых случаях. Тем не менее, в то же время оно приводит к несогласованности в системе типов и усложняет достижение полностью единообразной и интуитивной модели программирования. Примитивные типы часто лишены полезных свойств объектов, таких как наследование, полиморфизм, вызов методов без явного упаковывания/распаковывания и использование в качестве аргумента для шаблонных типов.
В данной работе будут теоретически рассмотрены последствия устранения явной разницы между примитивными и объектными типами из высокоуровневого управляемого языка программирования и описаны этапы и результаты реализации.

**Chapter 1: Foundations of Programming Language Type Systems**
*   **Типовая система**

Типовая система - это формальная синтаксическая и семантическая структура, сопоставляющая типы и программные конструкции (выражения, переменные, фукнции) для обеспечения четко определенного вычислительного поведения. Ее основные теоретические и практические назначения:

1) Корректность поведения программы
    С введением типовой системы становится возможной статическая верификация соблюдения ограничений типов, не допускающая к выполнению неверно типизированные программы. Данный механизм гарантирует
    * Безопасность выполнения - предотвращение неопределённого поведения за счёт блокировки запрещённых операций (например некорректные обращения к памяти в управляемых средах типа JVM/CLR)
    * Теоретическую обоснованность - соответствие двум фундаментальным принципам типобезопасности по Райту-Феллейзену:
        1. Прогресс: корректно типизированная программа не может застрять в промежуточном состоянии
        2. Сохранение: типы остаются согласованными на всех этапах вычисления"
2) Уровень абстракции кода
    Типовая система обеспечивает инкапсуляцию доменных инвариантов с помощью абстракций типов (абстрактные типы данных и интерфейсы) и позволяет формально специфицировать границы модулей.
3) Возможность оптимизаций
    Наличие статической типизации позволяет применять оптимизации на этапе компиляции (например, специализация обобщенных типов и статическое разрешение методов) и минимизировать время исполнения в управляемых средах за счёт уменьшения количества динамических проверок типов.


#### Статическая и динамическая типизации
1. **Статическая типизация** (Java, C#, Kotlin):
   - Валидность типа доказывается на этапе компиляции с помощью формальных суждений о принадлежности выражения к типу в данном контексте (Γ ⊢ e : τ)
   - Гарантирует типобезопасность по Райту-Феллейзену
   - Критично для управляемых языков программирования из-за возможности проверок безопасности памяти (например, верификатор байт-кода JVM) и эффективности Just In Time компиляции за счет встраивания методов, ориентированных на конкретный тип.

2. **Динамическая типизация** (Python, JavaScript):
   - Типы функций и выражений определяются во время исполнения.
   - Нет формальной гарантии типобезопасности, но есть возможность менять поведение объектов, модулей и классов во время исполнения.

Современные управляемые языки высокого уровня (Java, C#) преимущественно основаны на статической типизации, расширенной возможностями динамического анализа во время выполнения. Данный компромиссный подход позволяет сочетать строгость формальной верификации с практической гибкостью разработки, но противоречие между статическими гарантиями и динамической адаптируемостью продолжает оставаться предметом активных исследований.



### **1.2.1 Primitive Types in Managed Languages**

#### **1. Definition and Conceptual Foundation**
Примитивные типы (далее примитивные типы или примитивы) являются наиболее фундаментальным типом данных в языках программирования. В отличие от объектов, они:
- **Не ссылают на память**, а непосредственно являются значениями, обычно находящимися на стеке. У них заголовка объекта (object header), таблицы виртуальных методов (vtable), ссылочной идентичности (identity).
- Имеют **фиксированную семантику**, определяющуюся стандартами языка (например, Java JLS §4.2, C# ECMA-334 §8.3).
- **Не могут быть подтипами** или наследоваться и являются атомарными (базовыми) элементами в иерархии типов.

**Теоретический контекст**:
В теории типов примитивы являются простейшими случаями конструирования типа и не разлагаются на более простые типы.
Конструирование сложных типов происходит на их основе:
    - Произведения (кортежи, записи) — (Int, Bool)
    - Суммы (типы-суммы, перечисления) — data Maybe a = Nothing | Just a
    - Функции — Int → Bool
    - Рекурсивные типы — data List a = Nil | Cons a (List a)

Операции с примитивами напрямую транслируются в машинные инструкции (например, iadd в JVM).

In type theory, primitives are *ground types* (base cases for type construction). Their behavior is often hardware-mapped (e.g., IEEE 754 floats).

#### **2. Примеры в высокоуровневых языках **

| **Тип**               | Java                          | C#                            | C++ (for contrast)          |
|---------------------------|-------------------------------|-------------------------------|----------------------------|
| **Целые числа**         | `int` (32b), `long` (64b)     | `int` (32b), `long` (64b)     | `int` (platform-dependent) |
| **Числа с плавающей точкой**        | `float` (32b), `double` (64b) | `float` (32b), `double` (64b) | Same, with `long double`   |
| **Булевы значения**               | `boolean` (1b*)               | `bool` (8b)                   | `bool` (8b)                |
| **Символ**             | `char` (16b, UTF-16)          | `char` (16b, Unicode)         | `char` (8b), `wchar_t`     |



#### **3. Основные характеристики**

**A. Представление в памяти**
- **Аллокация на стеке** * (default for local variables in methods)
  ```java
  void foo() {
    int x = 42; // Память выделена непосредственно на стеке
  }
  ```

**B. Улучшения перформанса**
1. **Производительность на уровне процессора**
   - Арифметические операции с примитивами компилируются непосредственно во встроенные инструкции:
     ```nasm
     ; x86 assembly for 'a + b'
     mov eax, [a]
     add eax, [b]
     ```

2. **Локализация в кэше**
   - Линейная модель доступа к памяти (критично для больших вычислений)


#### **4. Роль примитивных типов в управляемых средах исполнения**
- **Специальные байт-код инструкции:**: В JVM: iload, iadd, fstore для операций с int, float и др.
                                        В CLR: аналогичные IL-команды (ldc.i4, add).
- **Оптимизации времени исполнения**:
    Escape-анализ: Размещение временных переменных на стеке вместо кучи.
    Интринсики: Замена вызовов методов (например, Math.sin()) на нативные CPU-инструкции.




Would you like to emphasize any specific aspect (e.g., security implications or hardware-level details)?

*   **1.2 Categories of Data Types**
    *   **1.2.1 Primitive Types:**
        *   Definition (built-in, fundamental, often value-based).
        *   Examples (integers, floats, booleans, characters - use examples relevant to managed languages like Java/C#/C++).
        *   Characteristics (fixed size, direct memory representation, performance implications).
    *   **1.2.2 Reference Types (Objects):**
        *   Definition (references/pointers to memory locations, based on classes/structures).
        *   Examples (instances of classes, arrays, strings).
        *   Characteristics (variable size, indirection, identity, methods, polymorphism).
    *   **1.2.3 Value Types (where applicable - e.g., C# `struct`)**:
        *   Definition (data stored directly, like primitives but can be user-defined).
        *   Comparison with primitives and reference types.
        *   Performance characteristics.
*   **1.3 Introduction to the Challenge:**
    *   Explain the conflict: Hardware works efficiently with fixed-size, stack-allocated primitives (integers, floats, booleans). Object-oriented programming often treats "everything" as objects (heap-allocated, reference semantics, polymorphism).
    *   Mention the need to reconcile these for performance and code consistency.

*  **1.4 TheTraditional Approach (Illustrative Example, maybe Java first):**
    *   Explicit distinction: `int` (primitive) vs. `Integer` (object).
    *   Explain Wrapper Types.
    *   Explain Boxing (primitive -> object) and Unboxing (object -> primitive).
    *   Discuss the overhead/cost of boxing (heap allocation, memory indirection).

*  **1.5 C#'s Approach: Explicit Value vs. Reference Types:**
    *   Explain C#'s `struct` (value type) and `class` (reference type) keyword.
    *   Clarify that primitives (`int`, `bool`, `float`) are *structs* (value types).
    *   Discuss how this means they are typically stack-allocated and passed by value.
    *   Explain that C# *also* has boxing/unboxing when a value type needs to be treated as `object` or an interface type. This is a different *mechanism* than Java's distinct wrapper types, but serves a similar purpose and incurs a similar cost.
    *   Highlight the programmer's responsibility to be aware of this distinction (`struct` vs. `class`).

*  **1.6 Kotlin's Approach: Abstracting the Primitive/Object Distinction:**
    *   Introduce Kotlin's philosophy: "Everything is an object" at the source code level.
    *   Show examples: `Int` (capital I), `Boolean`, etc. appear as objects with methods.
    *   **Crucial Point:** Explain that the *compiler* (specifically, the Kotlin-to-JVM/JS/Native compiler) is smart enough to determine *when* it's safe and efficient to represent these `Int` objects using JVM primitive `int` bytecode instructions.
    *   Explain *when* it *must* use the object representation (e.g., when the type argument is generic like `List<T>`, or when nullable types force potential null checks that primitive types don't support directly without a wrapper).
    *   Discuss the benefits: Code consistency, cleaner APIs (no need for separate primitive/wrapper functions), easier generics.
    *   Discuss the trade-offs: Potential for unexpected boxing if the compiler can't optimize (though the Kotlin team works hard to minimize this).

*  **1.7 The Role of Compiler Optimization (Tie it all together):**
    *   Expand on *how* languages like Kotlin (and modern JVM/CLR) perform these optimizations.
    *   Mention concepts like primitive specialization (Kotlin compiler), escape analysis, scalar replacement (JVM/CLR JIT), inlining.
    *   This directly addresses your observation: the primitive *representation* is indeed often a compiler optimization.


**Chapter 2: High-Level Managed Programming Languages**
*   **2.1 Definition and Characteristics**
    *   What defines "high-level"? (Abstraction, ease of use).
    *   What defines "managed"? (Runtime environment, automatic memory management).
    *   Examples (Java, C#, Python, Ruby, JavaScript - focus on those with distinct primitive/object models if relevant to your work).
*   **2.2 The Runtime Environment**
    *   Virtual Machines (JVM, CLR, etc.).
    *   Just-In-Time (JIT) Compilation (how it interacts with types).
*   **2.3 Automatic Memory Management (Garbage Collection)**
    *   How GC works (basic principles - tracing, reference counting).
    *   How GC interacts with object graphs and memory layout.
    *   Implications of value vs. reference types on GC overhead.

**Chapter 3: The Problem: Inconsistency with Primitive Types in Managed Languages**
*   **3.1 Lack of Uniformity in the Type System**
    *   Primitives are often *not* objects.
    *   Difficulty in treating primitives and objects uniformly (e.g., in collections, generics).
*   **3.2 Limitations in Object-Oriented Features**
    *   Primitives cannot have methods (in the same way objects do).
    *   Primitives don't participate in inheritance hierarchies (typically).
    *   Issues with polymorphism when primitives are involved.
*   **3.3 Performance and Overhead (if applicable)**
    *   Boxing and Unboxing:
        *   Explain what boxing is (wrapping a primitive in an object).
        *   Explain what unboxing is (extracting the primitive value).
        *   Discuss the performance and memory overhead associated with boxing/unboxing.
    *   *(Note: If your target language *doesn't* have explicit boxing/unboxing, focus more on the *conceptual* inconsistency rather than this specific mechanism).*
*   **3.4 Impact on Language Design and Features**
    *   Complexity in generics (e.g., `List<int>` vs `List<Integer>` in Java).
    *   Reflection capabilities (can you reflect on a primitive type in the same way as an object?).
    *   Nullability (primitives often cannot be null, unlike object references).

    **Chapter 4: Existing Approaches and Related Concepts**
*   **4.1 Languages with Uniform Object Models**
    *   Examples (Smalltalk, Ruby).
    *   How they treat everything as an object (even numbers, booleans).
    *   Advantages (consistency, flexibility).
    *   Disadvantages (potential performance overhead).
*   **4.2 Wrapper Classes / Boxing (Revisited)**
    *   Discuss standard library solutions (e.g., `Integer`, `Double` in Java, `int.Parse()` in C# - focusing on how they *wrap* primitives but don't *eliminate* them).
    *   How autoboxing/unboxing attempts to bridge the gap (Java).
*   **4.3 Value Types vs. Reference Types (C#, .NET)**
    *   Discuss how C# explicitly differentiates `struct` (value type) and `class` (reference type).
    *   How this provides some benefits of primitives (stack allocation, no GC overhead) while allowing user-defined types.
    *   How this *still* maintains a distinction from pure reference/object types.
*   **4.4 Research on Unified Type Systems**
    *   Look for academic papers or language design discussions related to type system uniformity, object models, or eliminating primitive/value distinctions. (This is your literature review part).

**Chapter 5: Theoretical Foundations for Eliminating Primitives**
*   This chapter bridges the gap between the general background and *your specific approach*. It should outline the theoretical basis for the solution you implemented.
*   **5.1 Principles of a Fully Unified Type System**
    *   What does it mean for *everything* to be an object?
    *   Implications for identity, state, and behavior.
*   **5.2 Designing Object Replacements for Primitives**
    *   How would a conceptual `Integer` object work? (Internal value storage, immutability often desired).
    *   How would operations (`+`, `-`, `*`) be handled? (Method calls vs. special compiler handling).
    *   Handling equality and identity (`==` vs. `.equals()`).
*   **5.3 Performance Considerations in a Unified Model**
    *   The inherent overhead of objects (header, reference).
    *   Potential compiler optimizations (e.g., recognizing immutable value objects and treating them more like values where possible - sometimes called "unboxed objects" or similar concepts).
    *   Impact on memory layout and cache efficiency.
*   **5.4 Impact on Memory Management**
    *   Increased number of objects -> potentially more GC pressure.
    *   How the GC might be optimized for uniform object models.
*   **5.5 Implications for Language Semantics**
    *   How expression evaluation changes (method calls instead of direct operations).
    *   Assignment semantics.
    *   Method signatures and return types.
*   **5.6 Implications for the Type System**
    *   Subtyping and inheritance hierarchies for the new 'primitive' objects.
    *   Generics and collections become simpler theoretically (always dealing with objects).

**Conclusion to the Theory Part**
*   Summarize the key theoretical challenges and concepts discussed.
*   Reiterate why the distinction between primitives and objects is a significant area of study in language design.
*   Briefly state how the following chapters (likely implementation, results, etc.) build upon the theoretical foundation laid here.

**References**
*   List all sources cited throughout the theory part (books on programming languages, language specifications, academic papers, relevant documentation).

**Tips for Writing the Theory Part:**

1.  **Define Terms Clearly:** Especially "primitive type," "reference type," "managed language," "type system," "boxing," etc.
2.  **Use Examples:** Illustrate concepts with code examples from languages relevant to your work (Java, C#, etc.).
3.  **Cite Your Sources:** Every piece of information that isn't common knowledge or your original thought needs a citation. This is crucial for academic integrity.
4.  **Connect to Your Work:** While theoretical, ensure the concepts discussed clearly relate to the problem you tackled and the solution you implemented. Chapter 5 is where this connection becomes most explicit.


### **References**
- Pierce, B. C. (2002). *Types and Programming Languages*. MIT Press.
- Wright, A. K., & Felleisen, M. (1994). *A Syntactic Approach to Type Soundness*.
- Siek, J. G., & Taha, W. (2006). *Gradual Typing for Functional Languages*.
[1] Blackburn, S. M., et al. *"The DaCapo Benchmarks: Java Benchmarking Development and Analysis."* OOPSLA 2004.
(например, Java JLS §4.2, C# ECMA-334 §8.3)

#### **References for Citations**
[1] Goetz, B. *"Java Performance: The Definitive Guide"*. O’Reilly, 2014.
[2] Kennedy, A. *"Pickler: Efficient Binary Serialization for .NET"*. POPL 2005.

**Suggested Thesis Additions**:
- Case study: Benchmarking `ArrayList<Integer>` vs. `int[]`
- Diagram: Memory layout comparison (object vs. primitive)
- Historical analysis: Primitive/object duality from ALGOL to modern languages