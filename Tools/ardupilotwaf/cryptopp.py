from waflib.Configure import conf

def configure(cfg):
    crypt_dir = cfg.path.find_or_declare('../modules/cryptopp').abspath()
    cfg.env.INCLUDES_CRYPTOPP = [crypt_dir]
    cfg.env.LIBPATH_CRYPTOPP = [crypt_dir]
    cfg.env.LIB_CRYPTOPP = ['cryptopp']

@conf
def libcryptopp(bld):
    bld.exec_command("make -j$(nproc) --directory=" + bld.path.find_or_declare('../../modules/cryptopp').abspath())
