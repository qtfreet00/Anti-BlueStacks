### Anti BlueStacks Android Emulator Demo

#### 这是一个绕过bst模拟器内核屏蔽模拟器特征路径和特征文件的一个绕过方式，主要展示的是一个绕过手段，具体技术完善和规则完善需要自己去补充

#### 反模拟器检测目前主要有两种手段，一种是定制libc，对open，stat，access函数入口进行判断，常用C函数将无法进行判断，可使用svc进行绕过，第二种更直接的可以定制内核，通常情况下，应用层完全无法直接进行检测，此Demo主要针对他规则方面的缺陷进行的绕过手段

bst模拟器在内核层对常用的io函数针对路径和特征文件绝对路径进行了强匹配，并且去除了/../绕过，使得常规的这种方式无法检测到特征文件，

核心代码：

```
static int is_file_v2_exists(const char *path) {
    char *dir = dirname(path);
    int cd = chdir(dir);
    if (cd != 0) {
        return 0;
    }
    char *base = basename(path);
    if (access(base, R_OK) == 0) {
        E("find v2 %s success", path);
        return 1;
    } else {
        E("find v2 %s error,error is %s", path, strerror(errno));
    }
    chdir("/");
    return 0;
}

static int is_file_v1_exists(const char *path) {
    if (access(path, R_OK) == 0) {
        E("find v1 %s success", path);
        return 1;
    } else {
        E("find v1 %s error,error is %s", path, strerror(errno));
    }
    return 0;
}

```

##### 检测的均为同一文件 `/data/.bluestacks.prop`，通过cd命令绕过它的强规则匹配，此方法同样可以作用于IOS的越狱屏蔽检测，也有很好的效果


