#include "dialog.h"
#include "ui_dialog.h"

using std::make_pair;

Dialog::Dialog(QWidget* parent) :
	QDialog(parent),
	ui(new Ui::Dialog)
{
	ui->setupUi(this);

	driveMenuScene = new QGraphicsScene(this);
	buildScene = new QGraphicsScene(this);
	buildView = new BuildCanvas(this, &menuManagerMain);
	buildView->setScene(buildScene);
	buildView->setGeometry(10, 120, 790, 360);
	buildView->setSceneRect(10, 120, 1000, 340);
	buildView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	buildView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

	loadGuiElelements();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateMenuManager()));
	timer->start(10);
}

Dialog::~Dialog()
{
	delete ui;
}

void Dialog::loadGuiElelements()
{
	ifstream fin;

	fin.open("Headers.txt");

	if (!fin)
	{
		exit(1);
	}

	std::string line;

	while (std::getline(fin, line))
	{
		keys.push_back(line);
	}

	foreach(string s, keys)
	{
		std::cout << s;
	}

	driveBlocks.push_back(new MenuItem(":/Icons/Resources/Drive GUI.png", MenuItem::DRIVEFORWARD, ui->driveTab));
	driveBlocks.push_back(new MenuItem(":/Icons/Resources/driveBack.png", MenuItem::DRIVEBACKWARD, ui->driveTab));
	driveBlocks.push_back(new MenuItem(":/Icons/Resources/rotateRight90.png", MenuItem::ROTATERIGHT, ui->driveTab));
	driveBlocks.push_back(new MenuItem(":/Icons/Resources/rotateLeft90.png", MenuItem::ROTATELEFT, ui->driveTab));

	driveBlocks.push_back(new MenuItem(":/Icons/Resources/Arm.png", MenuItem::GRABTOTE, ui->armTab));
	driveBlocks.push_back(new MenuItem(":/Icons/Resources/releaseArm.png", MenuItem::RELEASETOTE, ui->armTab));

	driveBlocks.push_back(new MenuItem(":/Icons/Resources/elevatorUp.png", MenuItem::ELEVATORUP, ui->elevatorTab));
	driveBlocks.push_back(new MenuItem(":/Icons/Resources/elevatorDown.png", MenuItem::ELEVATORDOWN, ui->elevatorTab));


	driveBlocks.push_back(new MenuItem(":/Icons/Resources/startAuto.png", MenuItem::AUTOSTART, ui->startStopTab));

	driveBlocks.push_back(new MenuItem(":/Icons/Resources/Timeout.png", MenuItem::TIMEOUT, ui->timeoutTab));


	menuManagerMain.changeCurrentMenu(&driveBlocks);

	int k = 0;
	for (int i = 0; i < driveBlocks.size(); i++)
	{
		if (i > 0)
		{
			if (driveBlocks.at(i)->parent() != driveBlocks.at(i - 1)->parent()) k = 0;
		}

		driveBlocks.at(i)->setGeometry(10 + (k * 80), 10, 61, 61);
		k++;
	}
}

void Dialog::on_graphicsView_destroyed()
{
}

void Dialog::updateMenuManager()
{
	timer->start(100);
	menuManagerMain.updateSelectedItem();
	buildView->updateCanvas();
}

void Dialog::on_generateButton_released()
{
	int sizeOfKeys = sizeof(keys) / sizeof(keys[0]);

	unordered_multimap<std::string, std::vector<string>*> outPutStuff;

	for (int i = 0; i < sizeOfKeys; i++)
	{
		outPutStuff.insert(std::make_pair<string, vector<string>*> (std::string(keys[i]), new std::vector<string>(sizeOfKeys)));
	}

	vector<unordered_multimap<string, string>*> commandIOVector;
	ofstream csvFile;
	string sendCommmandCode;

	vector<CommandBlock*> orderedCommands = buildView->orderConnections();
	vector<string> commandCode;
	for (int i = 0; i < orderedCommands.size(); i++)
	{
		orderedCommands.at(i)->getInputs();
		//ommandCode.push_back(std::to_string(orderedCommands.at(i)->getID()));
		commandIOVector.push_back(orderedCommands.at(i)->sendOutputs());
	}
	csvFile.open("./autonomousVariables.csv");

	sendCommmandCode = boost::algorithm::join(keys, ",");
	csvFile << sendCommmandCode << endl;

	for (auto i = 0; i < commandIOVector.size(); i++)
	{
		vector<string> outPutString;
		unordered_multimap<string, string>* currentCommand = commandIOVector.at(i);
		for (int k = 0; k < sizeOfKeys; k++)
		{
			std::unordered_map<std::string, string>::const_iterator place = currentCommand->find(std::string(keys[k]));
			if (place == currentCommand->end())
			{
				outPutString.push_back("0");
			}
			else
			{
				outPutString.push_back(place->second);
			}
		}
		//copy(outPutString.begin(), outPutString.end(), ostream_iterator<string>(send, ","));
		auto send = boost::algorithm::join(outPutString, ",");
		csvFile << send << endl;
	}

	csvFile.close();

	//sftp to the roboRIO
	system("python ./Python_Scripts/ftpCSV.py");
}

void Dialog::on_loadButton_released()
{
	buildView->wipe();

	std::unordered_map<std::string, vector<string>*> commandsIN;

	string value;
	string fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/lucas", tr("CSV Files (*.csv)")).toStdString();

	for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
	{
		io::CSVReader<1> in(fileName);
		in.read_header(io::ignore_extra_column, string(keys[i]));
		commandsIN.insert(std::make_pair<string, vector<string>*>(string(keys[i]), new vector<string>(sizeof(keys) / sizeof(keys[0]))));
		while (in.read_row(value))
		{
			std::unordered_map<std::string, vector<string>*>::const_iterator place = commandsIN.find(std::string(keys[i]));
			place->second->push_back(value);
		}
	}
	vector<CommandBlock *> commandsToSendToCanvas;
	int x = 10;
	int y = 300;

	commandsToSendToCanvas.push_back(new CommandBlock(CommandBlock::AUTOSTART));
	commandsToSendToCanvas.at(0)->setXY(x, y);
	commandsToSendToCanvas.at(0)->setUpConnectors(x, y);

	std::unordered_map<std::string, vector<string>*>::const_iterator place = commandsIN.find("ID");
	std::unordered_map<std::string, vector<string>*> dataWithoutWhiteSpaces;

	for (int i = 0; i < place->second->size(); i++)
	{
		if (!place->second->at(i).empty())
		{
			auto currentID = atoi(place->second->at(i).c_str());
			CommandBlock* newCommand;
			string value;
			vector<string*> constantKeys;
			x += 100;

			switch (currentID)
			{
			case(1):
				newCommand = new CommandBlock(CommandBlock::DRIVEFORWARD);
				break;
			case(-1):
				newCommand = new CommandBlock(CommandBlock::DRIVEBACKWARD);
				break;
			case(2):
				newCommand = new CommandBlock(CommandBlock::ROTATERIGHT);
				break;
			case(-2):
				newCommand = new CommandBlock(CommandBlock::ROTATELEFT);
				break;
			case(5):
				newCommand = new CommandBlock(CommandBlock::IDLE);
				constantKeys.push_back(new string("Time Out"));
				break;
			case(6):
				newCommand = new CommandBlock(CommandBlock::RELEASETOTE);
				break;
			case(-6):
				newCommand = new CommandBlock(CommandBlock::GRABTOTE);
				break;
			default:
				break;
			}
			newCommand->setXY(x, y);
			newCommand->setUpConnectors(x, y);

			for (auto key : constantKeys)
			{
				std::unordered_map<std::string, vector<string>*>::const_iterator newPlace = commandsIN.find(std::string(*key));
				value = newPlace->second->at(i);
				newCommand->getConnectorByName(*key)->setConstantReady();
				newCommand->getConnectorByName(*key)->getConstant()->setText(QString::fromStdString(value));
			}
			commandsToSendToCanvas.push_back(newCommand);
		}
	}
	buildView->addCommandsToCanvas(&commandsToSendToCanvas);
}

void Dialog::on_clearButton_released()
{
	buildView->wipe();
}