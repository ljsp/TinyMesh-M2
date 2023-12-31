#include "qte.h"
#include "implicits.h"
#include "Bezier.h"
#include "Deformation.h"
#include "ui_interface.h"
#include "Primitives.h"

MainWindow::MainWindow() : QMainWindow(), uiw(new Ui::Assets)
{
	// Chargement de l'interface
    uiw->setupUi(this);

	// Chargement du GLWidget
	meshWidget = new MeshWidget;
	QGridLayout* GLlayout = new QGridLayout;
	GLlayout->addWidget(meshWidget, 0, 0);
	GLlayout->setContentsMargins(0, 0, 0, 0);
    uiw->widget_GL->setLayout(GLlayout);

    uiw->meshOne_comboBox->addItem("None");
    uiw->meshOne_comboBox->addItem("Box");
    uiw->meshOne_comboBox->addItem("Sphere");
    uiw->meshOne_comboBox->addItem("Capsule");
    uiw->meshOne_comboBox->addItem("Torus");
    uiw->meshOne_comboBox->addItem("bunny");

    uiw->meshTwo_comboBox->addItem("None");
    uiw->meshTwo_comboBox->addItem("Box");
    uiw->meshTwo_comboBox->addItem("Sphere");
    uiw->meshTwo_comboBox->addItem("Capsule");
    uiw->meshTwo_comboBox->addItem("Torus");
    uiw->meshTwo_comboBox->addItem("bunny");

    uiw->operator_comboBox->addItem("None");
    uiw->operator_comboBox->addItem("Union");
    uiw->operator_comboBox->addItem("Intersection");
    uiw->operator_comboBox->addItem("Subtraction");
    uiw->operator_comboBox->addItem("Melange");

	// Creation des connect
	CreateActions();

	meshWidget->SetCamera(Camera(Vector(10, 0, 0), Vector(0.0, 0.0, 0.0)));
}

MainWindow::~MainWindow()
{
	delete meshWidget;
}

void MainWindow::CreateActions()
{
	// Buttons
    connect(uiw->boxMesh, SIGNAL(clicked()), this, SLOT(BoxMeshExample()));
    connect(uiw->boxImplicit, SIGNAL(clicked()), this, SLOT(BoxImplicitExample()));
    connect(uiw->sphereImplicit, SIGNAL(clicked()), this, SLOT(SphereImplicitExample()));
    connect(uiw->capsuleImplicit, SIGNAL(clicked()), this, SLOT(CapsuleImplicitExample()));
    connect(uiw->torusImplicit, SIGNAL(clicked()), this, SLOT(TorusImplicitExample()));
    connect(uiw->bunnyImplicit, SIGNAL(clicked()), this, SLOT(BunnyImplicitExample()));
    connect(uiw->customImplicit, SIGNAL(clicked()), this, SLOT(CustomImplicitExample()));
    connect(uiw->apply_operatorButton, SIGNAL(clicked()), this, SLOT(RenderObjects()));
    connect(uiw->addRay_Button, SIGNAL(clicked()), this, SLOT(IntersectRay()));
    connect(uiw->bezierPatch_Button, SIGNAL(clicked()), this, SLOT(BezierPatchExample()));
    connect(uiw->bezierCurve_Button, SIGNAL(clicked()), this, SLOT(BezierCurveExample()));
    connect(uiw->twist_Button, SIGNAL(clicked()), this, SLOT(TwistedBezierCurveExample()));
    connect(uiw->resetcameraButton, SIGNAL(clicked()), this, SLOT(ResetCamera()));
    connect(uiw->exportModel_Button, SIGNAL(clicked()), this, SLOT(SaveModel()));
    connect(uiw->wireframe, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_1, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_2, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));

	// Widget edition
	connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray&)), this, SLOT(editingSceneLeft(const Ray&)));
	connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray&)), this, SLOT(editingSceneRight(const Ray&)));
}

void MainWindow::editingSceneLeft(const Ray&)
{
}

void MainWindow::editingSceneRight(const Ray&)
{
}

void MainWindow::BoxMeshExample()
{
	Mesh boxMesh = Mesh(Box(1.0));

	std::vector<Color> cols;
	cols.resize(boxMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
		cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

	meshColor = MeshColor(boxMesh, cols, boxMesh.VertexIndexes());
	UpdateGeometry();
}

void MainWindow::CustomImplicitExample()
{
    BoxImplicit bunny(Vector(0.8));

    double translateX = uiw->translateX_doubleSpinBox->value();
    double translateY = uiw->translateY_doubleSpinBox->value();
    double translateZ = uiw->translateZ_doubleSpinBox->value();

    double scaleX = uiw->scaleX_doubleSpinBox->value();
    double scaleY = uiw->scaleY_doubleSpinBox->value();
    double scaleZ = uiw->scaleZ_doubleSpinBox->value();

    double rotateX = uiw->rotX_doubleSpinBox->value();
    double rotateY = uiw->rotY_doubleSpinBox->value();
    double rotateZ = uiw->rotZ_doubleSpinBox->value();

    Sphere torus(Vector(0.0), .1);

    Translate translate(&torus, Vector(translateX, translateY, translateZ));
    Scale scaleTorus(&translate, Vector(scaleX, scaleY, scaleZ));

    RotationY rotationY(&scaleTorus, rotateY);
    RotationX rotationX(&rotationY, rotateX);
    RotationZ rotationZ(&rotationX, rotateZ);

    SmoothSubtraction implicit(&rotationZ, &bunny, 0.3);
    //SmoothUnion implicit(&rotationZ, &scaleBunny, 0.3);

    Mesh implicitMesh;
    implicit.Polygonize(31, implicitMesh, Box(2.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::BunnyImplicitExample()
{
    Bunny implicit(0);

    Mesh implicitMesh;
    implicit.Polygonize(31, implicitMesh, Box(0.75));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::BoxImplicitExample()
{
    BoxImplicit implicit(Vector(0.8));

    Mesh implicitMesh;
    implicit.Polygonize(31, implicitMesh, Box(1.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::SphereImplicitExample()
{
  Sphere implicit(Vector(0.0), 1.0);

  Mesh implicitMesh;
  implicit.Polygonize(31, implicitMesh, Box(1.0));

  std::vector<Color> cols;
  cols.resize(implicitMesh.Vertexes());
  for (size_t i = 0; i < cols.size(); i++)
    cols[i] = Color(0.8, 0.8, 0.8);

  meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
  UpdateGeometry();
}

void MainWindow::CapsuleImplicitExample()
{
    Capsule implicit(Vector(0.0), Vector(1.0,0.0,.0), 0.5);

    Mesh implicitMesh;
    implicit.Polygonize(31, implicitMesh, Box(2.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::TorusImplicitExample() {

    Torus implicit(Vector(0.0), Vector(0.5, 0.3, 0.0));

    Mesh implicitMesh;
    implicit.Polygonize(31, implicitMesh, Box(1.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::BezierPatchExample()
{
    int n = uiw->patchLenght_spinBox->value();
    int m = uiw->patchWidth_spinBox->value();
    int res = uiw->res_spinBox->value();
    float offsetU = uiw->offsetU_doubleSpinBox->value();
    float offsetV = uiw->offsetV_doubleSpinBox->value();

    Bezier patch = Bezier::patch(n, m, res, offsetU, offsetV);

    Mesh patchMesh = patch.Polygonize();

    std::vector<Color> cols;
    cols.resize(patchMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

    meshColor = MeshColor(patchMesh, cols, patchMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::BezierCurveExample()
{
    int n = uiw->curveLenght_spinBox->value();
    int res = uiw->res_spinBox->value();
    float offsetU = uiw->offsetU_doubleSpinBox->value();
    float offsetV = uiw->offsetV_doubleSpinBox->value();

    Bezier curve = Bezier::curve(n, 10, offsetU, offsetV);

    /*std::vector<std::vector<Vector>> cp = curve.getControlPoints();
    printf("cp.size() = %d\n", cp.size());
    for (int i = 0; i < cp.size(); ++i) {
        for (int j = 0; j < cp[i].size(); ++j) {
            printf("{%f, %f, %f},\n", i, j, cp[i][j][0], cp[i][j][1], cp[i][j][2]);
        }
    }*/

    std::vector<std::vector<Vector>> cp =
            {
                {{Vector(0.000000, 0.000000, 0.930292)}},
                {{Vector(0.300000, 0.000000, 0.285240)}},
                {{Vector(0.600000, 0.000000, 0.435932)}},
                {{Vector(0.900000, 0.000000, 0.145050)}},
                {{Vector(1.200000, 0.000000, 0.640366)}},
                {{Vector(1.500000, 0.000000, 0.921713)}},
                {{Vector(1.800000, 0.000000, 0.626940)}},
                {{Vector(2.100000, 0.000000, 0.460799)}},
                {{Vector(2.400000, 0.000000, 0.657712)}},
                {{Vector(2.700000, 0.000000, 0.984499)}},
            };

    curve.setControlPoints(cp);

    Mesh curveMesh = curve.Polygonize();

    Mesh revolutionMesh = Bezier::Revolution(curveMesh, Vector(1,0,0), res);

    std::vector<Color> cols;
    cols.resize(revolutionMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

    meshColor = MeshColor(revolutionMesh, cols, revolutionMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::TwistedBezierCurveExample()
{
    int n = uiw->curveLenght_spinBox->value();
    int res = uiw->res_spinBox->value();
    float offsetU = uiw->offsetU_doubleSpinBox->value();
    float offsetV = uiw->offsetV_doubleSpinBox->value();

    Bezier curve = Bezier::curve(n, 10, offsetU, offsetV);

    /*std::vector<std::vector<Vector>> cp = curve.getControlPoints();
    printf("cp.size() = %d\n", cp.size());
    for (int i = 0; i < cp.size(); ++i) {
        for (int j = 0; j < cp[i].size(); ++j) {
            printf("{%f, %f, %f},\n", i, j, cp[i][j][0], cp[i][j][1], cp[i][j][2]);
        }
    }*/

    std::vector<std::vector<Vector>> cp =
            {
                    {{Vector(0.000000, 0.000000, 0.930292)}},
                    {{Vector(0.300000, 0.000000, 0.285240)}},
                    {{Vector(0.600000, 0.000000, 0.435932)}},
                    {{Vector(0.900000, 0.000000, 0.145050)}},
                    {{Vector(1.200000, 0.000000, 0.640366)}},
                    {{Vector(1.500000, 0.000000, 0.921713)}},
                    {{Vector(1.800000, 0.000000, 0.626940)}},
                    {{Vector(2.100000, 0.000000, 0.460799)}},
                    {{Vector(2.400000, 0.000000, 0.657712)}},
                    {{Vector(2.700000, 0.000000, 0.984499)}},
            };

    curve.setControlPoints(cp);

    Mesh curveMesh = curve.Polygonize();

    Twist twist(3.9, Vector(1,0,0));
    Mesh warpedMesh = twist.WarpMesh(curveMesh);

    Mesh revolutionMesh = Bezier::Revolution(warpedMesh, Vector(1,0,0), res);

    std::vector<Color> cols;
    cols.resize(revolutionMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(double(i) / 6.0, fmod(double(i) * 39.478378, 1.0), 0.0);

    meshColor = MeshColor(revolutionMesh, cols, revolutionMesh.VertexIndexes());
    UpdateGeometry();
}

void MainWindow::RenderObjects() {

    QString meshOne = uiw->meshOne_comboBox->currentText();
    QString meshTwo = uiw->meshTwo_comboBox->currentText();
    QString op = uiw->operator_comboBox->currentText();

    float meshOneSize = uiw->meshOne_sizeSpinBox->value();
    float meshTwoSize = uiw->meshTwo_sizeSpinBox->value();
    float k_value = uiw->k_valueSpinBox->value();

    Node * node1;
    Node * node2;

    switch (meshOne[0].toLatin1()) {
    case 'B':
        node1 = new BoxImplicit(Vector(meshOneSize));
        break;
    case 'S':
        node1 = new Sphere(Vector(0.0),meshOneSize);
        break;
    case 'C':
        node1 = new Capsule(Vector(0.0), Vector(1.0, 0.0, 0.0), meshOneSize);
        break;
    case 'T':
        node1 = new Torus(Vector(0.0), Vector(meshOneSize, meshOneSize, 0.0));
        break;
    case 'b':
        node1 = new Bunny(0);
        break;
    default:
        node1 = new BoxImplicit(Vector(0.0));
        break;
    }

    switch (meshTwo[0].toLatin1()) {
    case 'B':
        node2 = new BoxImplicit(Vector(meshTwoSize));
        break;
    case 'S':
        node2 = new Sphere(Vector(0.0), meshTwoSize);
        break;
    case 'C':
        node2 = new Capsule(Vector(0.0), Vector(1.0, 0.0, 0.0), meshTwoSize);
        break;
    case 'T':
        node2 = new Torus(Vector(0.0), Vector(meshTwoSize, meshTwoSize, 0.0));
        break;
    case 'b':
        node2 = new Bunny(0);
        break;
    default:
        node2 = new BoxImplicit(Vector(0.0));
        break;
    }

    switch (op[0].toLatin1()) {
    case 'I':
        implicit = new SmoothIntersection(node2, node1, k_value);
        break;
    case 'S':
        implicit = new SmoothSubtraction(node2, node1, k_value);
        break;
    case 'U':
        implicit = new SmoothUnion(node2, node1, k_value);
        break;
    case 'M':
        implicit = new Melange(node2, node1, k_value);
        break;
    default:
        implicit = new Union(node2, node1);
        break;
    }

    Mesh implicitMesh;
    implicit->Polygonize(31, implicitMesh, Box(1.0));

    std::vector<Color> cols;
    cols.resize(implicitMesh.Vertexes());
    for (size_t i = 0; i < cols.size(); i++)
        cols[i] = Color(0.8, 0.8, 0.8);

    meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());
    UpdateGeometry();

}

void MainWindow::IntersectRay()
{
    double posX = uiw->rayPosX_doubleSpinBox->value();
    double posY = uiw->rayPosY_doubleSpinBox->value();
    double posZ = uiw->rayPosZ_doubleSpinBox->value();

    double dirX = uiw->rayDirX_doubleSpinBox->value();
    double dirY = uiw->rayDirY_doubleSpinBox->value();
    double dirZ = uiw->rayDirZ_doubleSpinBox->value();

    Ray ray(Vector(posX, posY, posZ), Vector(dirX, dirY, dirZ));

    double t = -1.0;
    bool intersect = implicit->Intersect(ray, t);
    printf("Intersect: %d, t: %f\n", intersect, t);
    uiw->hit_Label->setText(QString::number(intersect));

    if (intersect) {
        double sphereSize = 0.1;
        double kVal = uiw->rayK_doubleSpinBox->value();
        Sphere* sphere = new Sphere(Vector(ray.Origin() + t * ray.Direction()), sphereSize);
        implicit = new SmoothSubtraction(implicit, sphere, .0);
        Mesh implicitMesh;
        implicit->Polygonize(31, implicitMesh, Box(2.0));

        std::vector<Color> cols;
        cols.resize(implicitMesh.Vertexes());
        for (size_t i = 0; i < cols.size(); i++)
            cols[i] = Color(0.0, 0.0, 1.0);

        meshColor = MeshColor(implicitMesh, cols, implicitMesh.VertexIndexes());

        //rays.emplace_back(std::make_pair(ray.Origin(), ray.Origin() + t * ray.Direction()));

        UpdateGeometry();
    }
}

inline void glPointDraw(const Vector & p) {
    glVertex3f(p[0], p[1], p[2]);
}

void MainWindow::UpdateGeometry()
{
	meshWidget->ClearAll();
	meshWidget->AddMesh("BoxMesh", meshColor);

    uiw->lineEdit->setText(QString::number(meshColor.Vertexes()));
    uiw->lineEdit_2->setText(QString::number(meshColor.Triangles()));

	UpdateMaterial();

    /*for (auto ray : rays) {
        glColor3d(0.0,1.0,0.0);
        glBegin(GL_LINE_STRIP);
        glPointDraw(ray.first);
        glPointDraw(ray.second);
        glEnd();
    }*/
}

void MainWindow::UpdateMaterial()
{
    meshWidget->UseWireframeGlobal(uiw->wireframe->isChecked());

    if (uiw->radioShadingButton_1->isChecked())
		meshWidget->SetMaterialGlobal(MeshMaterial::Normal);
	else
		meshWidget->SetMaterialGlobal(MeshMaterial::Color);
}

void MainWindow::ResetCamera()
{
	meshWidget->SetCamera(Camera(Vector(-10.0), Vector(0.0)));
}

void MainWindow::SaveModel() {
    Mesh implicitMesh;
    implicit->Polygonize(31, implicitMesh, Box(1.0));
    implicitMesh.SaveObj("model.obj", "model.obj");
}
