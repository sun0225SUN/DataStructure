p = rearA->next; 
rearA->next = rearB->next->next;	
rearB->next = p;
free(p);