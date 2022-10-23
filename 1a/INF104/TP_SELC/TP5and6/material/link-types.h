#IFNDEF "linked-list.h"
#DEFINE "linked-list.h"
typedef struct st udent {
 char lastname[30];
 char firstname[20];
 int group;
} Student_t;

typedef struct link{
     Student_t  student;
     struct link * next;
} Link_t;
#ENDIF "linked-list.h"
