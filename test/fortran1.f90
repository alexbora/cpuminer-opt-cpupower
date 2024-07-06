program main
 
implicit none
integer :: i, j, k 
integer, parameter :: n = 1000 
real(8) :: a(n,n), b(n,n), c(n,n) 
real(8) :: start, finish, elapsed 
print *, 'Matrix size = ', n 
do i = 1, n 
do j = 1, n 
a(i,j) = 1.0 
b(i,j) = 2.0 
c(i,j) = 0.0 
end do 
end do

end program main
