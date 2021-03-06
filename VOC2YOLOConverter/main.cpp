#include "mrdir.h"
#include "mropencv.h"
#include "mrutil.h"
#include "../VOCUtil/DataSetConfig.h"
#include "../VOCUtil/AnnotationFile.h"

void convert2ssdannotation(DatasetConfig &voc)
{
	vector<string>files;
	getAllFilesinDir(voc.rootdir + "/" + voc.imagedir, files);
	AnnotationFile::set_labelmaps(voc.classes);
	for (int imgindex = 0; imgindex < files.size(); imgindex++)
	{
		AnnotationFile af;
		cout << files[imgindex] << endl;
		string filepath = voc.rootdir + "/" + voc.imagedir + "/" + files[imgindex];
		string annotationfilepath = voc.rootdir + "/" + voc.annotationdir + "/" + files[imgindex].substr(0, files[imgindex].length() - 4) + ".xml";
		af.load_file(annotationfilepath);
		string newannopath = "labels/" + files[imgindex].substr(0, files[imgindex].length() - 4) + ".txt";
		af.save_txt(newannopath);
	}
}

void ProcessFiles(DatasetConfig &voc)
{
	vector<string>files;
	getAllFilesinDir(voc.rootdir+"/" + voc.imagedir, files);
	AnnotationFile::set_labelmaps(voc.classes);
	int imgindex = 0;
	if (files.size() == 0)
	{
		cout << "There is no img file in " << voc.rootdir + "/" + voc.imagedir << endl;
		return;
	}		
	while (true)
	{
		string filepath = voc.rootdir + "/" + voc.imagedir + "/" + files[imgindex];
		string annotationfilepath = voc.rootdir + "/" + voc.annotationdir + "/" + files[imgindex].substr(0,files[imgindex].length()-4)+".xml";	
		Mat img = imread(filepath);
		if (!img.data)
			break;
		AnnotationFile af;
		if (af.load_file(annotationfilepath))
		{
			af.drawannotation2Image(img);
			cout << files[imgindex] << endl;
			imshow("gt", img);
			string newannopath = "labels/" + files[imgindex].substr(0, files[imgindex].length() - 4) + ".txt";
			af.save_txt(newannopath);
		}
		char c=waitKey();
		switch (c)
		{
		case 'p':
		case 'P':
			imgindex=imgindex-1>0?imgindex-1:0;
			break;
		case 'n':
		case 'N':
			imgindex=imgindex<files.size()?imgindex+1:files.size()-1;
			break;
		}
	}
}

int showannotation(DatasetConfig &voc)
{
//	voc.vocinit();
//	voc.save_file("voc.xml");
	ProcessFiles(voc);
	return 0;
}

int main()
{
	DatasetConfig voc;
//	showannotation(voc);
	convert2ssdannotation(voc);
	return 0;
}