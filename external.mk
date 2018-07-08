SHBUF_USER_VERSION = 1.0
SHBUF_USER_SITE = /home/sam/buildroot/buildroot/package/shbuf_user
SHBUF_USER_SITE_METHOD = local

 
define SHBUF_USER_BUILD_CMDS
    $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D) all
endef
  
$(eval $(generic-package))
