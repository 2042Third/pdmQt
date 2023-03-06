/**
 * For PDM encrypted sqlite database
 * by Yi Yang
 * using github.com/viaduck/cryptoSQLite's GPL3 licenced library.
 * Nov 2022
 * */


#ifndef PDM_CRYPTO_DATABASE_HPP
#define PDM_CRYPTO_DATABASE_HPP

#include <cryptosqlite/crypto/IDataCrypt.h>
#include <cc20_multi.h> // pdm-crypt-module
#include "empp.h" // pdm-crypt-module api
#include "crypto_rand.hpp"

class pdm_crypto_db : public IDataCrypt {
public:
  void encrypt(uint32_t page, const Buffer &source, Buffer &destination, const Buffer &key) const override {
    // Encrypt with cc20
    cc20_utility::pure_crypt((uint8_t*)source.const_data(),(uint8_t*)destination.data()
        ,source.size(),( uint8_t*)key.const_data());
  }

  void decrypt(uint32_t page, const Buffer &source, Buffer &destination, const Buffer &key) const override {
    // Stream cypher xor
    encrypt(page,source,destination,key);
  }

  void generateKey(Buffer &destination) const override {
    size_t key_size= cc20_utility::nonce_key_pair_size();
    uint8_t key_pair[key_size+1];
    cc20_utility::gen_key_nonce_pair(key_pair,key_size); // generate the key and nonce randomly

    std::string str_key; str_key.resize(key_size);
    memcpy(str_key.data(),((char*)key_pair),key_size);
    String testKey(str_key);

    destination.write(testKey, 0);
    // TODO: cleanup the stack buffers.
  }

  void wrapKey(Buffer &wrappedKey, const Buffer &key, const Buffer &wrappingKey) const override {
    size_t key_size= cc20_utility::nonce_key_pair_size();
    crypto_rand crand;
    uint8_t tmp_buf[NONCE_SIZE+POLY_SIZE+1];
    crand.write_rand_bytes(tmp_buf,NONCE_SIZE+POLY_SIZE);
    wrappedKey.append(key);
    wrappedKey.append(tmp_buf,NONCE_SIZE+POLY_SIZE);
    cmd_enc_s(key.const_data()
        ,key_size
        ,(uint8_t*)wrappedKey.data()
        ,wrappingKey.const_data(), wrappingKey.size());

//    std::cout<<"key"<<std::endl;
//    print_stats(key.const_data(),key_size);
//    std::cout<<"Wrapped key"<<std::endl;
//    print_stats(wrappedKey.const_data(),key_size+NONCE_SIZE+POLY_SIZE);
//
//    std::cout<<"Wrapping key"<<std::endl;
//    print_stats(wrappingKey.const_data(),wrappingKey.size());
  }

  void unwrapKey(Buffer &key, const Buffer &wrappedKey, const Buffer &wrappingKey) const override {
    size_t key_size= cc20_utility::nonce_key_pair_size();

    cmd_dec_s(wrappedKey.const_data()
                                ,key_size+NONCE_SIZE+POLY_SIZE
                                ,(uint8_t*)key.data()
                                ,wrappingKey.const_data(), wrappingKey.size());

//    std::cout<<"key"<<std::endl;
//    print_stats(key.const_data(),key_size);
//    std::cout<<"Wrapped key"<<std::endl;
//    print_stats(wrappedKey.const_data(),key_size+NONCE_SIZE+POLY_SIZE);
//    std::cout<<"Wrapping key"<<std::endl;
//    print_stats(wrappingKey.const_data(),wrappingKey.size());
  }

  uint32_t extraSize() const override { return cc20_utility::nonce_key_pair_size()+NONCE_SIZE+POLY_SIZE+1; }
private:
  /**
   * Using the "secure memory" requires moving everything into normal memory.
   * This function does that.
   * */
  static void copy_to_normal_buffer(uint8_t*_dest,const Buffer & source, size_t size)  {
    for (uint32_t i=0;i<size;i++)
      _dest[i] = *source.const_data(i);
  }

  static void print_stats(const uint8_t* a,size_t size,int binary=1) {
    std::string ac ; ac.resize(size); memcpy(ac.data(),a,size);
    std::cout<< "Size : \""<<ac.size()<<"\""<<std::endl;
    if(!binary)std::cout<< "Plain: "<<ac<<std::endl;
    std::cout<< " Hax : \""<<stoh(ac)<<"\""<<std::endl;
    std::cout<< "Hash : \""<<get_hash(ac)<<"\""<<std::endl;
  }
};
#endif

