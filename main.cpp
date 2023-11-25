#include <Magick++.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>

using namespace std::filesystem;
using namespace Magick;
using namespace std;

void exec(std::string watermark, std::filesystem::path file, std::string dst)
{
  std::string thumbnailSize = "800x800";
  Image markwater(watermark);
  Image backgroundimage(file);
  backgroundimage.resize(Geometry(thumbnailSize));
  Geometry watermarkDimension(backgroundimage.size().width() / 1.5, backgroundimage.size().height() / 1.5);
  markwater.resize(watermarkDimension);
  // OverlayCompositeOp
  // OverCompositeOp
  backgroundimage.composite(markwater, CenterGravity, Magick::OverlayCompositeOp);
  backgroundimage.write(dst.append(file.filename()));
}

int main(int argc, char **argv)
{
  InitializeMagick(*argv);

  std::string watermark = argv[1];
  std::string src = argv[2];
  std::string dst = argv[3];

  if (watermark.empty() || src.empty() || dst.empty())
  {
    cout << "Invalid arguments!";
    return 1;
  }

  for (const auto &entry : directory_iterator(src))
  {
    try
    {
      std::filesystem::path filePath = entry.path();
      cout << "File name:" << filePath << endl;
      exec(watermark, filePath, dst);
    }
    catch (Exception &error_)
    {
      cout << "Caught exception: " << error_.what() << endl;
      return 1;
    }
  }

  return 0;
}
