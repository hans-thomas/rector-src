<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

interface ExtendsAbstractWithImplementationInterface {
    public function foo(): void;
}
abstract class ExtendsAbstractWithImplementationContract implements ExtendsAbstractWithImplementationInterface {}

final class ExtendsAbstractWithImplementationClass extends ExtendsAbstractWithImplementationContract
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    #[\Override]
    public function bar(): void
    {
        echo 'bar';
    }
}
?>
-----
<?php

namespace Rector\Tests\DeadCode\Rector\ClassMethod\RemoveUselessOverrideAttributeRector\Fixture;

interface ExtendsAbstractWithImplementationInterface {
    public function foo(): void;
}
abstract class ExtendsAbstractWithImplementationContract implements ExtendsAbstractWithImplementationInterface {}

final class ExtendsAbstractWithImplementationClass extends ExtendsAbstractWithImplementationContract
{
    #[\Override]
    public function foo(): void
    {
        echo 'foo';
    }

    public function bar(): void
    {
        echo 'bar';
    }
}
?>
