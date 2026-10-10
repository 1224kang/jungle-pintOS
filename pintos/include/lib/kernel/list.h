#ifndef __LIB_KERNEL_LIST_H
#define __LIB_KERNEL_LIST_H

// ## 이중 연결 리스트 (Doubly Linked List)

// 이 이중 연결 리스트 구현은 동적 메모리 할당을 필요로 하지 않습니다. 대신 리스트의 요소가 될 수 있는 각 구조체는 `struct list_elem` 멤버를 내부에 포함해야 합니다.

// 모든 리스트 함수는 이러한 `struct list_elem`을 대상으로 동작합니다. `list_entry` 매크로를 사용하면 `struct list_elem`에서 이를 포함하고 있는 원래 구조체 객체로 변환할 수 있습니다.

// 예를 들어 `struct foo`의 리스트가 필요하다고 가정해 보겠습니다. `struct foo`는 다음과 같이 `struct list_elem` 멤버를 포함해야 합니다.

// ```
// struct foo {
//     struct list_elem elem;
//     int bar;
//     // ... 다른 멤버들 ...
// };
// ```

// 그다음 `struct foo`의 리스트를 다음과 같이 선언하고 초기화할 수 있습니다.

// ```
// struct list foo_list;

// list_init(&foo_list);
// ```

// 리스트를 순회하는 과정에서는 `struct list_elem`에서 이를 포함하는 원래 구조체로 변환해야 하는 경우가 많습니다.

// 다음은 `foo_list`를 순회하는 예시입니다.

// ```
// struct list_elem *e;

// for (e = list_begin(&foo_list);
//      e != list_end(&foo_list);
//      e = list_next(e)) {
//     struct foo *f = list_entry(e, struct foo, elem);
//     // ... f를 이용한 작업 수행 ...
// }
// ```

// 실제 소스 코드 전반에서 리스트 사용 예시를 찾아볼 수 있습니다. 예를 들어 `threads` 디렉터리의 `malloc.c`, `palloc.c`, `thread.c`에서도 리스트를 사용합니다.

// 이 리스트의 인터페이스는 C++ STL의 `list<>` 템플릿에서 영감을 받았습니다. 따라서 `list<>`에 익숙하다면 이 리스트도 쉽게 사용할 수 있을 것입니다.

// 하지만 이러한 리스트는 타입 검사를 수행하지 않으며, 올바르게 사용되고 있는지에 대한 검증도 거의 수행하지 못한다는 점을 강조해야 합니다. 잘못 사용하면 심각한 문제가 발생할 수 있습니다.

// ### 리스트 용어 정리

// - front: 리스트의 첫 번째 요소입니다. 빈 리스트에서는 정의되지 않습니다. `list_front()`가 반환합니다.
// - back: 리스트의 마지막 요소입니다. 빈 리스트에서는 정의되지 않습니다. `list_back()`이 반환합니다.
// - tail: 리스트의 마지막 요소 바로 뒤에 있다고 간주되는 요소입니다. 빈 리스트에서도 정의됩니다. `list_end()`가 반환하며, 앞에서 뒤로 리스트를 순회할 때 종료를 나타내는 센티널(sentinel)로 사용됩니다.
// - beginning: 리스트가 비어 있지 않으면 첫 번째 요소이고, 비어 있으면 tail입니다. `list_begin()`이 반환하며, 앞에서 뒤로 리스트를 순회할 때 시작점으로 사용됩니다.
// - head: 리스트의 첫 번째 요소 바로 앞에 있다고 간주되는 요소입니다. 빈 리스트에서도 정의됩니다. `list_rend()`가 반환하며, 뒤에서 앞으로 리스트를 순회할 때 종료를 나타내는 센티널로 사용됩니다.
// - reverse beginning: 리스트가 비어 있지 않으면 마지막 요소이고, 비어 있으면 head입니다. `list_rbegin()`이 반환하며, 뒤에서 앞으로 리스트를 순회할 때 시작점으로 사용됩니다.
// - interior element: head나 tail이 아닌 실제 리스트 요소를 의미합니다. 빈 리스트에는 interior element가 존재하지 않습니다.

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* List element. */
struct list_elem {
	struct list_elem *prev;     /* Previous list element. */
	struct list_elem *next;     /* Next list element. */
};

/* List. */
struct list {
	struct list_elem head;      /* List head. */
	struct list_elem tail;      /* List tail. */
};

/* 
elem 주소만 있으면 struct thread 전체의 시작 주소를 계산->모든 필드 접근 가능
*/
#define list_entry(LIST_ELEM, STRUCT, MEMBER)           \
	((STRUCT *) ((uint8_t *) &(LIST_ELEM)->next     \
		- offsetof (STRUCT, MEMBER.next)))

void list_init (struct list *);

/* List traversal. */
struct list_elem *list_begin (struct list *);
struct list_elem *list_next (struct list_elem *);
struct list_elem *list_end (struct list *);

struct list_elem *list_rbegin (struct list *);
struct list_elem *list_prev (struct list_elem *);
struct list_elem *list_rend (struct list *);

struct list_elem *list_head (struct list *);
struct list_elem *list_tail (struct list *);

/* List insertion. */
void list_insert (struct list_elem *, struct list_elem *);
void list_splice (struct list_elem *before,
		struct list_elem *first, struct list_elem *last);
void list_push_front (struct list *, struct list_elem *);
void list_push_back (struct list *, struct list_elem *);

/* List removal. */
struct list_elem *list_remove (struct list_elem *);
struct list_elem *list_pop_front (struct list *);
struct list_elem *list_pop_back (struct list *);

/* List elements. */
struct list_elem *list_front (struct list *);
struct list_elem *list_back (struct list *);

/* List properties. */
size_t list_size (struct list *);
bool list_empty (struct list *);

/* Miscellaneous. */
void list_reverse (struct list *);

/* Compares the value of two list elements A and B, given
   auxiliary data AUX.  Returns true if A is less than B, or
   false if A is greater than or equal to B. */
typedef bool list_less_func (const struct list_elem *a,
                             const struct list_elem *b,
                             void *aux);

/* Operations on lists with ordered elements. */
void list_sort (struct list *,
                list_less_func *, void *aux);
void list_insert_ordered (struct list *, struct list_elem *,
                          list_less_func *, void *aux);
void list_unique (struct list *, struct list *duplicates,
                  list_less_func *, void *aux);

/* Max and min. */
struct list_elem *list_max (struct list *, list_less_func *, void *aux);
struct list_elem *list_min (struct list *, list_less_func *, void *aux);

#endif /* lib/kernel/list.h */
