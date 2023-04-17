from waflib.Configure import conf

def configure(cfg):
    cfg.env.CRYPTOPP_LIB = 'libcryptopp.a'
    cfg.env.CRYPTOPP_DIR = cfg.path.find_or_declare('../modules/cryptopp').abspath()

@conf
def libcryptopp(bld):
    bld.exec_command("make -j$(nproc) --directory=" + bld.env.CRYPTOPP_DIR)
