      subroutine allocate_acc(dim1)
      use dopiqState
      implicit none
      integer dim1
      if (inuse .eq. 0) then
c        print *,  "dopiq: allocating"
         inuse = 1
         dim1_acc = dim1
         allocate(acc(dim1))
      endif
      end
      
      subroutine deallocate_acc()
      use dopiqstate
      if (inuse .ne. 0) then
c        print *,  "dopiq: deallocating"
         deallocate(acc)
         inuse = 0
      endif
      end

      integer function inuse_acc()
      use dopiqstate
      inuse_acc = inuse
      return
      end
