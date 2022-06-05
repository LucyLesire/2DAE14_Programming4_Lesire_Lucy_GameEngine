#pragma once
#include "RenderComponent.h"
#include "Font.h"

namespace dae
{
	class ImageComponent final : public RenderComponent
	{
	public:

		void Update(float deltaTime) override;
		void FixedUpdate(float fDT) override;
		void LateUpdate(float) override {};
		void Initialize() override;

		explicit ImageComponent(const std::string& fileName);
		ImageComponent() = default;
		virtual ~ImageComponent() = default;
		ImageComponent(const ImageComponent& other) = delete;
		ImageComponent(ImageComponent&& other) = delete;
		ImageComponent& operator=(const ImageComponent& other) = delete;
		ImageComponent& operator=(ImageComponent&& other) = delete;

		void SetSheetSize(Transform2D size) { m_SheetSize = size; }
		Transform2D GetSheetSize() const { return m_SheetSize; }

	private:
		Transform2D m_SheetSize{};
	};
}


