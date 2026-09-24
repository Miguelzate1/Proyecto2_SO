// Recorre kmem.freelist y cuenta cuántas páginas libres hay actualmente.
uint64
countfreepages(void)
{
  struct run *r;
  uint64 n = 0;

  acquire(&kmem.lock);
  r = kmem.freelist;
  while(r){
    n++;
    r = r->next;
  }
  release(&kmem.lock);

  return n;
}