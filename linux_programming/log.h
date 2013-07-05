#ifndef _LOG_H_
#define _LOG_H_

#include<stdio.h>

#define LOGP(msg,arg...) printf(msg, ##arg)
#define LOGI(msg,arg...) printf("%s:%d:%s() " msg "\n", __FILE__, __LINE__, __func__, ##arg)

#endif /* _LOG_H_ */
