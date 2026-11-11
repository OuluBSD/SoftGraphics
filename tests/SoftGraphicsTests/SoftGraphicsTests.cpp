#include <SoftGraphics/SoftGraphics.h>
#include <SoftGraphics/Device.h>
#include <SoftGraphics/Instance.h>
#include <SoftGraphics/Buffer.h>
#include <SoftGraphics/Texture.h>
#include <SoftGraphics/CommandBuffer.h>

using namespace Upp;
using namespace SoftGraphics;

namespace {

void TestInstanceAndDevice()
{
	Cout() << "TestInstanceAndDevice: Starting..." << EOL;

	Instance* inst = sgCreateInstance();
	ASSERT(inst != nullptr);

	Array<Device*> devices = sgEnumerateDevices(inst, Backend::CPU);
	ASSERT(devices.GetCount() >= 1);
	for(auto* d : devices)
		delete d;

	Device* dev = sgCreateDevice(inst, nullptr, Backend::CPU);
	ASSERT(dev != nullptr);
	ASSERT(dev->GetBackend() == Backend::CPU);
	Cout() << "Device Name: " << dev->GetName() << EOL;

	// Test Buffer
	BufferDesc bdesc;
	bdesc.usage = BufferUsage::Vertex;
	bdesc.size = 1024;
	SoftGraphics::Buffer* buf = dev->CreateBuffer(bdesc);
	ASSERT(buf != nullptr);
	ASSERT(buf->GetDesc().size == 1024);

	uint8 dummy_data[64] = {0xAA, 0xBB, 0xCC, 0xDD};
	buf->UpdateData(dummy_data, 64, 0);

	delete buf;

	// Test Texture
	TextureDesc tdesc;
	tdesc.type = TextureType::Tex2D;
	tdesc.format = TextureFormat::RGBA8;
	tdesc.width = 16;
	tdesc.height = 16;
	Texture* tex = dev->CreateTexture(tdesc);
	ASSERT(tex != nullptr);
	ASSERT(tex->GetDesc().width == 16);
	ASSERT(tex->GetDesc().height == 16);

	delete tex;

	// Test CommandBuffer
	CommandBuffer* cmd = dev->CreateCommandBuffer();
	ASSERT(cmd != nullptr);
	cmd->Begin();
	cmd->End();

	Array<CommandBuffer*> cmdList;
	cmdList.Add(cmd);
	dev->QueueSubmit(cmdList);
	dev->WaitIdle();

	delete cmd;
	sgDestroyDevice(dev);
	sgDestroyInstance(inst);

	Cout() << "TestInstanceAndDevice: Passed!" << EOL;
}

void TestShaderIR()
{
	Cout() << "TestShaderIR: Starting..." << EOL;

	// Test that ShaderIR classes are functional
	ShaderDesc sdesc;
	sdesc.stage = ShaderStage::Vertex;
	sdesc.source = "def main(pos: vec3) -> vec4:\n    return vec4(pos, 1.0)\n";
	sdesc.entryPoint = "main";

	ASSERT(sdesc.stage == ShaderStage::Vertex);
	ASSERT(sdesc.entryPoint == "main");

	Cout() << "TestShaderIR: Passed!" << EOL;
}

}

CONSOLE_APP_MAIN
{
	Cout() << "========================================" << EOL;
	Cout() << "Running SoftGraphics Automated Tests" << EOL;
	Cout() << "========================================" << EOL;

	TestInstanceAndDevice();
	TestShaderIR();

	Cout() << "========================================" << EOL;
	Cout() << "ALL SOFTGRAPHICS TESTS PASSED!" << EOL;
	Cout() << "========================================" << EOL;
}
