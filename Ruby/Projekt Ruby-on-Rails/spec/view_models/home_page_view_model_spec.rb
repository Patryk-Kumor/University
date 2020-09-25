require 'rails_helper'

RSpec.describe HomePageViewModel do
  describe '#featured_product' do
    subject { described_class.new.featured_product }

    it { is_expected.to be_nil }

    context 'when products exist' do
      let!(:product1) { create :product }
      let!(:product2) { create :product }

      it { is_expected.to eq(product2) }
    end
  end

  describe '#new_products' do
    subject { described_class.new.new_products }

    it { is_expected.to be_empty }

    context 'when products exist' do
      let!(:product1) { create :product }
      let!(:product2) { create :product }

      it { is_expected.to eq([product1]) }

      context 'when there are more than 3 products' do
        let!(:product3) { create :product }
        let!(:product4) { create :product }
        let!(:product5) { create :product }

        it { is_expected.to eq([product4, product3, product2]) }
      end
    end
  end

  describe '#popular_products' do
    subject { described_class.new.popular_products }

    it { is_expected.to be_empty }

    context 'when products exist' do
      let!(:product1) { create :product }
      let!(:product2) { create :product }
      let!(:product3) { create :product }
      let!(:product4) { create :product }

      it { is_expected.to eq([product4, product3, product2]) }

      context 'when comments exist' do
        let!(:product1_comments) { create_list :comment, 2, product: product1 }
        let!(:product2_comment) { create :comment, product: product2 }

        it { is_expected.to eq([product1, product2, product4]) }
      end
    end
  end
end
