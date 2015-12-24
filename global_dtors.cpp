
namespace {

struct AtExitData {
  void (*dtor)(void *);
  void *obj;
  void *dso;
};

const int MAX_GLOBAL_DTORS = 1024;
int num_global_dtors = 0;
AtExitData global_dtors[MAX_GLOBAL_DTORS];

} // unnamed namespace

extern "C" {

int __cxa_atexit(void (*dtor)(void *), void *obj, void *dso)
{
  if (num_global_dtors == MAX_GLOBAL_DTORS) {
    return -1;
  }

  global_dtors[num_global_dtors].dtor = dtor;
  global_dtors[num_global_dtors].obj = obj;
  global_dtors[num_global_dtors].dso = dso;
  ++num_global_dtors;

  return 0;
}

void __cxa_finalize(void *dso)
{
  if (dso == nullptr) {
    while (num_global_dtors > 0) {
      AtExitData &data = global_dtors[--num_global_dtors];
      if (data.dtor != nullptr) {
        data.dtor(data.obj);
        data.dtor = nullptr;
      }
    }
  } else {
    for (int i = 0; i < num_global_dtors; ++i) {
      AtExitData &data = global_dtors[i];
      if (data.dso == dso) {
        if (data.dtor != nullptr) {
          data.dtor(data.obj);
          data.dtor = nullptr;
        }
        break;
      }
    }
  }
}

}
