#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utime.h>
#include <sys/time.h>
#include <sys/stat.h>

#ifdef __hermit__

#define UNUSED(x) (void)(x)

char * getcwd(char *buf, size_t size) {
    UNUSED(buf);
    UNUSED(size);
    return NULL; // Hermit does not support getcwd
}


int utimes(const char *path, const struct timeval times[2]) {
    UNUSED(path);
    UNUSED(times);
    errno = ENOSYS; // Hermit does not support utimes
    return -1;
}

int chroot(const char *dirname) {
    UNUSED(dirname);
    errno = ENOSYS; // Hermit does not support chroot
    return -1;  
}

int lchown(const char *path, uid_t owner, gid_t group) {
    UNUSED(path);
    UNUSED(owner);
    UNUSED(group);
    errno = ENOSYS; // Hermit does not support lchown
    return -1; 
}

int fchown(int fildes, uid_t owner, gid_t group) {
    UNUSED(fildes);
    UNUSED(owner);
    UNUSED(group);
    errno = ENOSYS; // Hermit does not support fchown
    return -1; 
}

int fchdir(int fildes) {
    UNUSED(fildes);
    errno = ENOSYS; // Hermit does not support fchown
    return -1; 
}

int fchmod(int fildes, mode_t mode) {
    UNUSED(fildes);
    UNUSED(mode);
    errno = ENOSYS; // Hermit does not support fchmod
    return -1;
}

pid_t getppid(void) {
    return 0; // Hermit does not support getppid
}

pid_t getpgrp(void) {
    return 0; // Hermit does not support getpgrp
}

mode_t umask(mode_t cmask) {
    UNUSED(cmask);
    return 0; // Hermit does not support umask
}

int mknod(const char *path, mode_t mode, dev_t dev) {
    UNUSED(path);
    UNUSED(mode);
    UNUSED(dev);
    errno = ENOSYS; // Hermit does not support fchmod
    return -1;
}

int pause(void) {
    errno = ENOSYS; // Hermit does not support pause
    return -1;
}

int setregid(gid_t rgid, gid_t egid) {
    UNUSED(rgid);
    UNUSED(egid);
    errno = ENOSYS; // Hermit does not support setregid
    return -1;
}

int setreuid(uid_t ruid, uid_t euid) {
    UNUSED(ruid);
    UNUSED(euid);
    errno = ENOSYS; // Hermit does not support setreuid
    return -1;
}

int sethostname(const char *name, size_t namelen) {
    UNUSED(name);
    UNUSED(namelen);
    errno = ENOSYS; // Hermit does not support sethostname
    return -1;
}

int setdomainname(const char *name, int namelen) {
    UNUSED(name);
    UNUSED(namelen);
    errno = ENOSYS; // Hermit does not support setdomainname
    return -1;
}

int madvise(void *addr, size_t len, int advice) {
    UNUSED(addr);
    UNUSED(len);
    UNUSED(advice);
    errno = ENOSYS; // Hermit does not support madvise
    return -1;
}

ssize_t pread(int fd, void *buf, size_t nbyte, off_t offset) {
    UNUSED(fd);
    UNUSED(buf);
    UNUSED(nbyte);
    UNUSED(offset);
    errno = ENOSYS; // Hermit does not support pread
    return -1;
}

ssize_t pwrite(int fildes, const void *buf, size_t nbyte, off_t offset) {
    UNUSED(fildes);
    UNUSED(buf);
    UNUSED(nbyte);
    UNUSED(offset);
    errno = ENOSYS; // Hermit does not support pwrite
    return -1;
}

int settimeofday(const struct timeval *tp, const struct timezone *tzp) {
    UNUSED(tp);
    UNUSED(tzp);
    errno = ENOSYS; // Hermit does not support settimeofday
    return -1;
}

int socketpair(int domain, int type, int protocol, int socket_vector[2]){
    UNUSED(domain);
    UNUSED(type);
    UNUSED(protocol);
    UNUSED(socket_vector);
    errno = ENOSYS; // Hermit does not support socketpair
    return -1;
}

int fstatat(int fd, const char *path, struct stat *buf, int flag) {
    UNUSED(fd);
    UNUSED(path);
    UNUSED(buf);
    UNUSED(flag);
    errno = ENOSYS; // Hermit does not support fstatat
    return -1;
}

int setgroups(int ngroups, const gid_t *gidset) {
    UNUSED(ngroups);
    UNUSED(gidset);
    errno = ENOSYS; // Hermit does not support setgroups
    return -1;
}

int getgroups(int gidsetsize, gid_t grouplist[]) {
    UNUSED(gidsetsize);
    UNUSED(grouplist);
    errno = ENOSYS; // Hermit does not support getgroups
    return -1;
}

int utime(const char *path, const struct utimbuf *times) {
    UNUSED(path);
    UNUSED(times);
    errno = ENOSYS; // Hermit does not support utime
    return -1;

}

int mount(const char *type, const char *dir, int flags, void *data) {
    UNUSED(type);
    UNUSED(dir);
    UNUSED(flags);
    UNUSED(data);
    errno = ENOSYS; // Hermit does not support mount
    return -1;
}

int truncate(const char *path, off_t length) {
    UNUSED(path);
    UNUSED(length);
    errno = ENOSYS; // Hermit does not support truncate
    return -1;


}

int fdatasync(int fd) {
    UNUSED(fd);
    errno = ENOSYS; // Hermit does not support fdatasync
    return -1;
}

int mkfifo(const char *path, mode_t mode) {
    UNUSED(path);
    UNUSED(mode);
    errno = ENOSYS; // Hermit does not support mkfifo
    return -1;
}

void sync(void) {
}

int __go_openat (int fd, char *path, int flags, mode_t mode)
{
    UNUSED(fd);
    UNUSED(path);
    UNUSED(flags);
    UNUSED(mode);
    errno = ENOSYS; // Hermit does not support __go_openat
    return -1;  
}

#endif
